#include "pch.h"
#include "ChessGame.h"
#include "Logger.h"
#include "Position.h"
#include "Enums.h"

std::vector<Move> ChessGame::generateMoves(Color color) {
    std::vector<Move> generatedMoves;
    if (color == Color::NONE) return generatedMoves;

    generatedMoves.reserve(256);

    forEachSquare([&](const Position& from) {
        const Piece& piece = board[from.x][from.y];

        // nur die passenden Pieces
        if (piece.color != color) return;

        // Alle möglichen Zielfelder
        forEachSquare([&](const Position& to) {
            if (from.x == to.x && from.y == to.y) return;

            Move m(from, to);
            if (isLegal(m)) {
                Log.tprefix("generateMoves/FoundMove").info("Valid Move found for " + board[from.x][from.y].getPieceName() + "." + std::to_string(from.x) + "|" + std::to_string(from.y) + " -> " +
                    std::to_string(to.x) + "|" + std::to_string(to.y));
                Extra isDouble = m.isMoveDouble(board[from.x][from.y].color) ? Extra::DOUBLE : Extra::NONE;
                generatedMoves.emplace_back(from, to, isDouble);
            }
        });
    });
    std::cout << "---------> Calcuated " << generatedMoves.size() << " Moves for party " << (color == Color::WHITE ? "white" : "black") << "!\n";
    return generatedMoves;
}

bool ChessGame::isLegal(const Move& move) {
    const Piece& srcP = board[move.from.x][move.from.y];
    const Piece& tgtP = board[move.to.x][move.to.y];

    if (move.from.inBoard() &&
        srcP.exists() &&
        srcP.color != tgtP.color &&
        pieceCanMoveLikeThat(move) &&
        !wouldBeInCheckAfterMove(move))
        return true;
    Log.tprefix("isLegal/SPAM").info("Move " + std::to_string(move.from.x) + "|" + std::to_string(move.from.y) + " -> " +
        std::to_string(move.to.x) + "|" + std::to_string(move.to.y) + " turned out illegal.");
    return false;
}

bool ChessGame::pieceCanMoveLikeThat(const Move& move) const {
    const Piece& srcP = board[move.from.x][move.from.y];
    using enum PieceType;

    switch (srcP.type) {
    case PAWN:   return canPawnMove(move);
    case ROOK:   return canRookMove(move);
    case KNIGHT: return canKnightMove(move);
    case BISHOP: return canBishopMove(move);
    case QUEEN:  return canQueenMove(move);
    case KING:   return canKingMove(move);
    default: return false;
    }
    
}

bool ChessGame::pathClear(const Move& move) const {
    int deltaX = move.to.x - move.from.x;
    int deltaY = move.to.y - move.from.y;
    int absDeltaX = abs(deltaX);
    int absDeltaY = abs(deltaY);
    if (!((deltaX == 0) || (deltaY == 0) || (absDeltaX == absDeltaY)))
        return false;

    int directionX = (deltaX == 0) ? 0 : ((deltaX > 0) ? 1 : -1);
    int directionY = (deltaY == 0) ? 0 : ((deltaY > 0) ? 1 : -1);
    int stepNumber = std::max(absDeltaX, absDeltaY);

    for (int i = 1; i < stepNumber; ++i) {
        int x = move.from.x + i * directionX;
        int y = move.from.y + i * directionY;
        if (getPieceAt(Position(x, y))->exists()) return false;
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
        move.isMoveDouble(src.color) &&
        !tgt.exists() && //tgt doesnt have a piece on it
        pathClear(move) //the piece in the middle is empty
        ) return true;
    // Capture Move´& Enpassant
    else if (
        abs(move.to.x - move.from.x) == 1 && //move is one to the right or left
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
    if (tgt.enPassantable) std::cout << tgt.enPassantable << std::endl;
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

bool ChessGame::canKnightMove(const Move& move) const {
    const Piece& src = board[move.from.x][move.from.y];
    const Piece& tgt = board[move.to.x][move.to.y];
    MoveType type = move.getMoveType();
    if (!src.exists() || src.type != PieceType::KNIGHT) {
        Log.tprefix("canKnightMove/Incorrect-Call").warn("Function 'ChessGame::canKnightMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Knight'");
        return false;
    }

    return (type == MoveType::LSHAPE && !tgt.isColor(src.color));
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

bool ChessGame::canKingMove(const Move& move) const {
    const Piece& src = board[move.from.x][move.from.y];
    const Piece& tgt = board[move.to.x][move.to.y];
    MoveType type = move.getMoveType();
    int absDeltaX = abs(move.to.x - move.from.x);
    int absDeltaY = abs(move.to.y - move.from.y);

    if (!src.exists() || src.type != PieceType::KING) {
        Log.tprefix("canKingMove/Incorrect-Call").warn("Function 'ChessGame::canKingMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'King'");
        return false;
    }

    return type <= MoveType::DIAGONAL && type >= MoveType::HORIZONTAL &&
        !tgt.isColor(src.color) &&
        absDeltaX <= 1 && absDeltaY <= 1;
}