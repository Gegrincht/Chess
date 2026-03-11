#pragma once
#include <array>
#include <vector>
#include <stdexcept>
#include <utility>

enum class PieceType { NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum class Color { NONE, WHITE, BLACK };
enum class MoveType { NONE, HORIZONTAL, VERTICAL, DIAGONAL, LSHAPE};

struct Position {
    int x;
    int y;

    Position() = default;
    Position(int x, int y);
    
    bool operator==(const Position& other);
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

    Move(int fx, int fy, int tx, int ty);
    
    MoveType getMoveType() const;

    bool operator==(const Move& other) const;
};

class ChessGame {
    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookAMoved = false;
    bool whiteRookHMoved = false;
    bool blackRookAMoved = false;
    bool blackRookHMoved = false;


    const Piece* getPieceAt(int x, int y) const;
    bool tryMove(Move& move);
    std::vector<Move> generateMoves(Color color) const;
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

    const Piece* getPieceAt(char x, int y) const;
    bool tryMove(char fx, int fy, char tx, int ty);
    bool isLegal(const Move& move) const;
    bool inCheck(Color color) const;
    bool isCheckmate(const Color color) const;
    bool isStalemate(const Color color) const;
    bool pathClear(const Move& m) const;
};


namespace Helpers {
    int colCharToIndex(char col);

    bool outOfBoard(int x);
    bool outOfBoard(int x, int y);

    void toLower(std::string& s);
}
