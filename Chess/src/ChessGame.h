#pragma once
#include <array>
#include <vector>
#include <stdexcept>

enum class PieceType { NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum class Color { NONE, WHITE, BLACK };

struct Piece {
    PieceType type = PieceType::NONE;
    Color color;

    Piece() = default;
    Piece(PieceType giventype, Color givencolor);
};

using Board = std::array<std::array<Piece, 8>, 8>;

struct Move {
    int fromX, fromY;
    int toX, toY;
    Color allowedParty;

    Move(Board& board, int ifromX, int ifromY, int itoX, int itoY);
};

class ChessGame {
    std::vector<Move> whiteMoves;
    std::vector<Move> blackMoves;

    Piece* getPieceAt(int x, int y);
    bool movePiece(int fromX, int fromY, int toX, int toY);
    std::vector<Move> generateMoves(Color color) const;
    std::vector<Move> getMoves(int x, int y) const;
public:
    Board board; // Create the Board

    ChessGame(); // Constructor
    Piece* getPieceAt(char x, int y);
    bool movePiece(char fromX, int fromY, char toX, int toY);
};

static int colCharToIndex(char col); 

static bool outOfBoard(int x);