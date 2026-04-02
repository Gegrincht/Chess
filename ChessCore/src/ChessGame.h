#pragma once
#include "pch.h"
#include "Enums.h"
#include "Piece.h"
#include "Move.h"
#include "Position.h"
#include <optional>


class ChessGame {
    Color toMove = Color::WHITE;
    std::array<std::array<Piece, 8>, 8> board;

    std::vector<Move> curMoves;

    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookAMoved = false;
    bool whiteRookHMoved = false;
    bool blackRookAMoved = false;
    bool blackRookHMoved = false;

    std::vector<Move> generateMoves(Color color);
    bool wouldBeInCheckAfterMove(const Move& move);
    bool pieceCanMoveLikeThat(const Move& move) const;
    bool isLegal(const Move& move);

    // Individual Piece Movement Checks
    bool canPawnMove(const Move& move) const;
    bool canRookMove(const Move& move) const;
    bool canKnightMove(const Move& move) const;
    bool canBishopMove(const Move& move) const;
    bool canQueenMove(const Move& move) const;
    bool canKingMove(const Move& move) const;

    void enPassantReset();
    void castleUpdate();

    void afterMoveHandler();
public:
    ChessGame();

    const Color getCurrentPlayer() const;

    bool tryMove(const Move& move);
    const Piece* getPieceAt(const Position& pos) const;
    bool tryMove(const Position& from, const Position& to);
    bool inCheck(Color color) const;
    bool isCheckmate(const Color color) const;
    bool isStalemate(const Color color) const;
    bool pathClear(const Move& move) const;
    
    void clearBoard();
    void setPiece(const Position& pos, const Piece& p);
    void resetBoard();

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
    template<typename Func>
    void forEachSquare(Func f) const {
        Position pos;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                pos.x = x; pos.y = y;
                f(pos);
            }
        }
    }
};