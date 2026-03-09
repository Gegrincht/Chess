#include "ChessGame.h"
#include "iostream"
#include <cstdlib>

bool ChessGame::pieceCanMoveLikeThat(const Move& move) const {
    const Piece& srcP = board[move.fromX][move.fromY];
    using enum PieceType;

    // TODO LIST ->>>>>>>>>>>>>>> REDO ENTIRE SECTION BASED ON THIS: https://chatgpt.com/c/69a38f04-ac9c-832d-9dd3-1ef26d8e3fce 
    switch (srcP.type) {
    case PieceType::PAWN:   return canPawnMove(move);
    case PieceType::ROOK:   return canRookMove(move);
    //case PieceType::KNIGHT: return canKnightMove(move);
    //case PieceType::BISHOP: return canBishopMove(move);
    //case PieceType::QUEEN:  return canQueenMove(move);
    //case PieceType::KING:   return canKingMove(move);
    default: return false;
    }
    
}

bool ChessGame::pathClear(const Move& move) const {   
    bool vertMove = move.fromX == move.toX;
    bool horiMove = move.fromY == move.toY;

    // linear moves

    if (vertMove || horiMove)
    {
        unsigned int amt = horiMove
            ? std::abs(static_cast<int>(move.fromX) - static_cast<int>(move.toX))
            : std::abs(static_cast<int>(move.fromY) - static_cast<int>(move.toY));
        if (vertMove) {
            for (int i = 1; i < amt; i++) {
                int newY = (move.toY > move.fromY) ? move.fromY + i : move.fromY - i;
                if (getPieceAt(move.fromX, newY)->exists()) return false;
        }   }
        else {
            for (int i = 1; i < amt; i++) {
                int newX = (move.toX > move.fromX) ? move.fromX + i : move.fromX - i;
                if (getPieceAt(newX, move.fromY)->exists()) return false;
            }
        }
    }
    // diagonal movement will be implemented later
    return true;
}

bool ChessGame::canPawnMove(const Move& move) const {
    const Piece& src = board[move.fromX][move.fromY];
    const Piece& tgt = board[move.toX][move.toY];
    int dir = (src.color == Color::WHITE) ? 1 : -1;
    // Check if canPawnMove was called correctly
    if (!src.exists() || src.type != PieceType::PAWN) {
        Helpers::logError("Function 'ChessGame::canPawnMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Pawn'");
        return false; 
    }
    // Forward move
    if (
        move.fromX == move.toX && // it doesnt move horizontally
        move.fromY + dir == move.toY && // Piece can move in that direction and only moves one
        !tgt.exists() // Target does not have a Piece
        ) return true;
    // Inital two-square move
    else if (
        !src.hasMoved && // has not moved yet
        move.fromX == move.toX && // it doesnt move horizontally
        move.fromY + (2 * dir) == move.toY && // moves two forward
        !tgt.exists() && //tgt doesnt have a piece on it
        pathClear(move) //the piece in the middle is empty
        ) return true;
    // Capture Move´& Enpassant
    else if (
        (move.fromX + 1 == move.toX || move.fromX - 1 == move.toX) && //move is one to the right or left
        move.fromY + dir == move.toY) { // move moves one forward
        const Piece& enpTGT = board[move.toX][move.toY - dir];
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
    else return false;
}

bool ChessGame::canRookMove(const Move& move) const {

}