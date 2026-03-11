#include "ChessGame.h"
#include "Logger.h"
#include "iostream"
#include <cstdlib>
#include <string>

std::vector<Move> ChessGame::generateMoves(Color color) const { // calls every chess pieces moves and puts it all in a vector 
    std::vector<Move> generatedMoves;
    if (color == Color::NONE) return generatedMoves;

    generatedMoves.reserve(256); // sollte für alles reichen und ein bischen mehr

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board[x][y].color != color || board[x][y].type == PieceType::NONE)
                continue;

            for (int tx = 0; tx < 8; tx++) {
                for (int ty = 0; ty < 8; ty++) {
                    if (x == tx && y == ty) continue;
                    if (isLegal(Move(x, y, tx, ty)))
                        generatedMoves.emplace_back(Move(x, y, tx, ty));
                }
            }
        }
    }
    return generatedMoves;
}

bool ChessGame::isLegal(const Move& move) const {
    const Piece& srcP = board[move.from.x][move.from.y];
    const Piece& tgtP = board[move.to.x][move.to.y];

    if (!Helpers::outOfBoard(move.from.x, move.from.y) &&
        srcP.exists() &&
        srcP.color != tgtP.color &&
        pieceCanMoveLikeThat(move))
        return true;
    Log.tprefix("isLegal/SPAM").info("Move " + std::to_string(move.from.x) + "|" + std::to_string(move.from.y) + " -> " +
        std::to_string(move.from.x) + "|" + std::to_string(move.from.y) + " turned out illegal.");
    return false;
}

bool ChessGame::pieceCanMoveLikeThat(const Move& move) const {
    const Piece& srcP = board[move.from.x][move.from.y];
    using enum PieceType;

    switch (srcP.type) {
    case PAWN:   return canPawnMove(move);
    case ROOK:   return canRookMove(move);
    //case KNIGHT: return canKnightMove(move);
    case BISHOP: return canBishopMove(move);
    case QUEEN:  return canQueenMove(move);
    //case KING:   return canKingMove(move);
    default: return false;
    }
    
}

bool ChessGame::pathClear(const Move& move) const {
    int deltaX = move.to.x - move.from.x;
    int deltaY = move.to.y - move.from.y;
    int absDeltaX = std::abs(deltaX);
    int absDeltaY = std::abs(deltaY);
    if (!((deltaX == 0) || (deltaY == 0) || (absDeltaX == absDeltaY)))
        return false;

    int directionX = (deltaX == 0) ? 0 : ((deltaX > 0) ? 1 : -1);
    int directionY = (deltaY == 0) ? 0 : ((deltaY > 0) ? 1 : -1);
    int stepNumber = std::max(absDeltaX, absDeltaY);

    for (int i = 1; i < stepNumber; ++i) {
        int x = move.from.x + i * directionX;
        int y = move.from.y + i * directionY;
        if (getPieceAt(x, y)->exists()) return false;
    }

    return true;
}

/// -------------------
/// CAN __________ MOVE
/// -------------------

bool ChessGame::canPawnMove(const Move& move) const {
    const Piece& src = board[move.from.x][move.from.y];
    const Piece& tgt = board[move.to.x][move.to.y];
    int dir = (src.color == Color::WHITE) ? 1 : -1;
    // Check if canPawnMove was called correctly
    if (!src.exists() || src.type != PieceType::PAWN) {
        Log.tprefix("canPawnMove/Incorrect-Call").warn("Function 'ChessGame::canPawnMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Pawn'");
        return false; 
    }
    // Forward move
    if (
        move.from.x == move.to.x && // it doesnt move horizontally
        move.from.y + dir == move.to.y && // Piece can move in that direction and only moves one
        !tgt.exists() // Target does not have a Piece
        ) return true;
    // Inital two-square move
    else if (
        !src.hasMoved && // has not moved yet
        move.from.x == move.to.x && // it doesnt move horizontally
        move.from.y + (2 * dir) == move.to.y && // moves two forward
        !tgt.exists() && //tgt doesnt have a piece on it
        pathClear(move) //the piece in the middle is empty
        ) return true;
    // Capture Move´& Enpassant
    else if (
        (move.to.x - move.from.x) == 1 && //move is one to the right or left
        move.from.y + dir == move.to.y) { // move moves one forward
        const Piece& enpTGT = board[move.to.x][move.to.y - dir];
        if (// Normal Take
            tgt.exists() && !tgt.isColor(src.color) // target has to exist and be opposite color
            ) return true;

        else if (
            enpTGT.type == PieceType::PAWN && // Target that did the double forward is a Pawn
            !enpTGT.isColor(src.color) &&  // Target is of the opposite Color
            tgt.enPassantable // block i want to move to is actually enPassantable  and someone didnt just do two one moves.
            ) return true;
    }
    // Invalid Move
    return false;
}

bool ChessGame::canRookMove(const Move& move) const {
    const Piece& src = board[move.from.x][move.from.y];
    const Piece& tgt = board[move.to.x][move.to.y];
    MoveType type = move.getMoveType();
    using enum MoveType;
    if (!src.exists() || src.type != PieceType::ROOK) {
        Log.tprefix("canRookMove/Incorrect-Call").warn("Function 'ChessGame::canRookMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Rook'");
        return false;
    }

    return (type == HORIZONTAL || type == VERTICAL) &&
        pathClear(move) &&
        !tgt.isColor(src.color);
}

bool ChessGame::canBishopMove(const Move& move) const {
    const Piece& src = board[move.from.x][move.from.y];
    const Piece& tgt = board[move.to.x][move.to.y];
    MoveType type = move.getMoveType();
    using enum MoveType;
    if (!src.exists() || src.type != PieceType::BISHOP) {
        Log.tprefix("canBishopMove/Incorrect-Call").warn("Function 'ChessGame::canBishopMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Bishop'");
        return false;
    }

    return (type == DIAGONAL) &&
        pathClear(move) &&
        !tgt.isColor(src.color);
}

bool ChessGame::canQueenMove(const Move& move) const {
    const Piece& src = board[move.from.x][move.from.y];
    const Piece& tgt = board[move.to.x][move.to.y];
    MoveType type = move.getMoveType();
    using enum MoveType;
    if (!src.exists() || src.type != PieceType::QUEEN) {
        Log.tprefix("canQueenMove/Incorrect-Call").warn("Function 'ChessGame::canQueenMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Queen'");
        return false;
    }

    return (type >= HORIZONTAL && type <= DIAGONAL) &&
        pathClear(move) &&
        !tgt.isColor(src.color);
}