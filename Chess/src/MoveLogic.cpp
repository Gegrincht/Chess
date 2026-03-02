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
    case PieceType::KNIGHT: return canKnightMove(move);
    case PieceType::BISHOP: return canBishopMove(move);
    case PieceType::QUEEN:  return canQueenMove(move);
    case PieceType::KING:   return canKingMove(move);
    default: return false;
    }
    
}

bool ChessGame::pathClear(const Move& move) const {   
    bool vertMove = move.fromX == move.toX;
    bool horiMove = move.fromY == move.toY;

    // liniare

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
    // diagonale kommt später
    return true;
}

bool ChessGame::canPawnMove(const Move& move) const {
    const Piece& src = board[move.fromX][move.fromY];
    const Piece& tgt = board[move.toX][move.toY];
    int dir = (src.color == Color::WHITE) ? 1 : -1;
    // Check if canPawnMove was called correctly
    if (!src.exists() || src.type != PieceType::PAWN) {
        std::cout << "Function 'ChessGame::canPawnMove' was called incorrectly cause either: Source Piece doesnt exists | or | Source Piece Type isnt 'Pawn'" << std::endl;
        return false; 
    }
    // Forward move
    if (
        move.fromX == move.toX && // it doesnt move horizontally
        move.fromY + dir == move.toY && // Piece can move in that direction and only moves one
        !tgt.exists() // Target does not have a Piece
        ) return true;
    // Inital two-square move
    if (
        !src.hasMoved;
        move.fromX == move.toX && // it doesnt move horizontally
        move.fromY + (2 * dir) == move.toY &&
        !tgt.exists() &&
        pathClear(move)
        ) return true;
    // Capture Move

    // Invalid Move
    return false;
}