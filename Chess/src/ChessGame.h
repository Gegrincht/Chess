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
    
};

using Board = std::array<std::array<Piece, 8>, 8>; // defines the chess board

struct Move {
    unsigned int fromX : 3;
    unsigned int fromY : 3;
    unsigned int toX : 3;
    unsigned int toY : 3;

    Move(unsigned int ifromX, unsigned int ifromY, unsigned int itoX, unsigned int itoY);
    
    bool operator==(const Move& other) const;
};

class ChessGame {
    Piece* getPieceAt(int x, int y);
    bool movePiece(Move& move);
    std::vector<Move> generateMoves(Color color) const;
    std::vector<Move> getMoves(int x, int y) const; // Checks what moves the Piece at that location has.
    bool wouldBeInCheckAfterMove(const Move& move) const; //can be const as it simulates
public:
    Board board; // Create the Board
    std::vector<Move> whiteMoves;
    std::vector<Move> blackMoves;

    ChessGame(); // Constructor

    Piece* getPieceAt(char x, int y);
    bool movePiece(char fromX, int fromY, char toX, int toY);
    bool isLegal(Move& move) const;
    bool inCheck(Color color) const;
    bool isCheckmate(Color color) const;
    bool isStalemate(Color color) const;

    bool isEmpty(const Piece& p);
    bool isEmpty(int x, int y) { return isEmpty(board[x][y]); }

    bool isEnemy(const Piece& p);
    bool isEnemy(int x, int y) { return isEnemy(board[x][y]); }
};

static int colCharToIndex(char col); 

static bool outOfBoard(int x);

static void toLower(std::string& s);