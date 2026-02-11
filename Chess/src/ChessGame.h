#pragma once
#include <array>
#include <vector>
#include <stdexcept>

enum class PieceType { NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum class Color { NONE, WHITE, BLACK };

struct Piece {
    PieceType type = PieceType::NONE;
    Color color = Color::NONE;

    Piece() = default;
    Piece(PieceType giventype, Color givencolor);

    char getPieceIcon() const;
    std::string getPieceName() const;
private:
    void toLower(std::string& s) const;
    
};

using Board = std::array<std::array<Piece, 8>, 8>; // defines the chess board

struct Move {
    unsigned int fromX : 3;
    unsigned int fromY : 3;
    unsigned int toX : 3;
    unsigned int toY : 3;

    Color allowedParty;



    Move(Board& board, unsigned int ifromX, unsigned int ifromY, unsigned int itoX, unsigned int itoY);
};

class ChessGame {
    std::vector<Move> whiteMoves;
    std::vector<Move> blackMoves;

    Piece* getPieceAt(int x, int y);
    bool movePiece(Move move);
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