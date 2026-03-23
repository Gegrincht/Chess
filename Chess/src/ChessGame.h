#pragma once
#include <array>
#include <vector>
#include <stdexcept>
#include <utility>

enum class PieceType { NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum class Extra { NONE, DOUBLE };
enum class Color { NONE, WHITE, BLACK };
enum class MoveType { NONE, HORIZONTAL, VERTICAL, DIAGONAL, LSHAPE};

struct Position {
    int x;
    int y;

    Position() = default;
    Position(int x, int y);
    Position(char x, int y);
    
    bool operator==(const Position& other);

    int colCharToIndex(char col) const;
    bool inBoard() const;
};

struct Piece {
    PieceType type = PieceType::NONE;
    Color color = Color::NONE;
    bool hasMoved;
    bool enPassantable;

    Piece() = default;
    Piece(PieceType giventype, Color givencolor);

    char getPieceIcon() const;
    std::string getPieceName() const;
    bool isColor(Color exColor) const;
    bool exists() const;
};

using Board = std::array<std::array<Piece, 8>, 8>; // defines the chess board

struct Move {
    Position from;
    Position to;
    MoveType moveType;
    Extra ex;

    Move(const Position& from, const Position& to, Extra ex = Extra::NONE);
    
    void isEnpassant() const;
    MoveType getMoveType() const;

    bool isMoveDouble(Color src) const;
    bool operator==(const Move& other) const;
};

class ChessGame {
    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookAMoved = false;
    bool whiteRookHMoved = false;
    bool blackRookAMoved = false;
    bool blackRookHMoved = false;

    std::vector<Move> generateMoves(Color color);
    bool wouldBeInCheckAfterMove(const Move& move) const; // simulates move
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
    Board board; // Create the Board

    ChessGame(); // Constructor

    bool tryMove(const Move& move);
    const Piece* getPieceAt(const Position& pos) const;
    bool tryMove(const Position& from, const Position& to);
    bool isLegal(const Move& move) const;
    bool inCheck(Color color) const;
    bool isCheckmate(const Color color) const;
    bool isStalemate(const Color color) const;
    bool pathClear(const Move& m) const;
    template<typename Func>
    void forEachSquare(Func f) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                f(Position(x, y));
            }
        }
    }
};

namespace Helpers {
    int colCharToIndex(char col);
    void toLower(std::string& s);
}
