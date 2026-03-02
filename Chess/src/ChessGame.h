#pragma once
#include <array>
#include <vector>
#include <stdexcept>
#include <utility>

enum class PieceType { NONE, PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
enum class Color { NONE, WHITE, BLACK };

struct Piece {
    PieceType type = PieceType::NONE;
    Color color = Color::NONE;
    bool hasMoved;

    Piece() = default;
    Piece(PieceType giventype, Color givencolor);

    char getPieceIcon() const;
    std::string getPieceName() const;
    bool isColor(Color exColor) const;
    bool exists() const;

};

using Board = std::array<std::array<Piece, 8>, 8>; // defines the chess board

struct Move {
    int fromX;
    int fromY;
    int toX;
    int toY;

    Move(unsigned int ifromX, unsigned int ifromY, unsigned int itoX, unsigned int itoY);
    
    bool operator==(const Move& other) const;
};

class ChessGame {
    const Piece* getPieceAt(int x, int y) const;
    bool movePiece(Move& move);

    bool whiteKingMoved = false;
    bool blackKingMoved = false;
    bool whiteRookAMoved = false;
    bool whiteRookHMoved = false;
    bool blackRookAMoved = false;
    bool blackRookHMoved = false;

    std::vector<Move> generateMoves(Color color) const;
    std::vector<Move> getMoves(int x, int y) const; // Checks what moves the Piece at that location has.
    bool wouldBeInCheckAfterMove(const Move& move) const; //can be const as it simulates
    bool pieceCanMoveLikeThat(const Move& move) const;

    // Individual Piece Movement Checks
    bool canPawnMove(const Move& move) const;
    bool canRookMove(const Move& move) const;
    bool canKnightMove(const Move& move) const;
    bool canBishopMove(const Move& move) const;
    bool canQueenMove(const Move& move) const;
    bool canKingMove(const Move& move) const;
public:
    Board board; // Create the Board
    std::vector<Move> whiteMoves;
    std::vector<Move> blackMoves;

    ChessGame(); // Constructor

    const Piece* getPieceAt(char x, int y) const;
    bool movePiece(char fromX, int fromY, char toX, int toY);
    bool isLegal(const Move& move) const;
    bool inCheck(Color color) const;
    bool isCheckmate(const Color color) const;
    bool isStalemate(const Color color) const;
    bool pathClear(const Move& m) const;
};

static int colCharToIndex(char col); 

static bool outOfBoard(int x);
static bool outOfBoard(int x, int y);

static void toLower(std::string& s);