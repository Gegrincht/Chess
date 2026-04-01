#pragma once
#include "pch.h"
#include "Enums.h"
#include "Piece.h"
#include "Move.h"
#include "Position.h"


class ChessGame {
    std::array<std::array<Piece, 8>, 8> board;
    Color toMove = Color::WHITE;

    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookAMoved = false;
    bool whiteRookHMoved = false;
    bool blackRookAMoved = false;
    bool blackRookHMoved = false;

    std::vector<Move> generateMoves(Color color);
    bool wouldBeInCheckAfterMove(const Move& move) const;
    bool pieceCanMoveLikeThat(const Move& move) const;

    // Individual Piece Movement Checks
    bool canPawnMove(const Move& move) const;
    bool canRookMove(const Move& move) const;
    bool canKnightMove(const Move& move) const;
    bool canBishopMove(const Move& move) const;
    bool canQueenMove(const Move& move) const;
    bool canKingMove(const Move& move) const;

    void enPassantReset();
public:
    ChessGame();

    bool tryMove(const Move& move);
    const Piece* getPieceAt(const Position& pos) const;
    bool tryMove(const Position& from, const Position& to);
    bool isLegal(const Move& move) const;
    bool inCheck(Color color) const;
    bool isCheckmate(const Color color) const;
    bool isStalemate(const Color color) const;
    bool pathClear(const Move& move) const;

    void resetBoard();
    void clearBoard();
    void setPiece(const Position& pos, const Piece& p);

    void switchTurnColor(Color next);

    /// <summary>
    /// Iterates over each square in an 8x8 grid and invokes a function for each position.
    /// </summary>
    /// <param name="f">A callable object (function, lambda, or functor) to invoke for each square position.</param>
    template<typename Func>
    void forEachSquare(Func f) {
        Position pos;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                pos.x = x; pos.y = y;
                f(pos);
            }
        }
    }
};