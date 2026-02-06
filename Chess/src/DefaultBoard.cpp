#include "ChessGame.h"
#include <array>

using Board = std::array<std::array<Piece, 8>, 8>;

Board initDefaultBoard() {
    Board board{}; // all default Pieces (PieceType::NONE)

    // Pawns
    for (int x = 0; x < 8; x++) {
        board[x][1] = Piece(PieceType::PAWN, Color::WHITE);
        board[x][6] = Piece(PieceType::PAWN, Color::BLACK);
    }

    // Rooks
    board[0][0] = Piece(PieceType::ROOK, Color::WHITE);
    board[7][0] = Piece(PieceType::ROOK, Color::WHITE);
    board[0][7] = Piece(PieceType::ROOK, Color::BLACK);
    board[7][7] = Piece(PieceType::ROOK, Color::BLACK);

    // Knights
    board[1][0] = Piece(PieceType::KNIGHT, Color::WHITE);
    board[6][0] = Piece(PieceType::KNIGHT, Color::WHITE);
    board[1][7] = Piece(PieceType::KNIGHT, Color::BLACK);
    board[6][7] = Piece(PieceType::KNIGHT, Color::BLACK);

    // Bishops
    board[2][0] = Piece(PieceType::BISHOP, Color::WHITE);
    board[5][0] = Piece(PieceType::BISHOP, Color::WHITE);
    board[2][7] = Piece(PieceType::BISHOP, Color::BLACK);
    board[5][7] = Piece(PieceType::BISHOP, Color::BLACK);

    // Queens
    board[3][0] = Piece(PieceType::QUEEN, Color::WHITE);
    board[3][7] = Piece(PieceType::QUEEN, Color::BLACK);

    // Kings
    board[4][0] = Piece(PieceType::KING, Color::WHITE);
    board[4][7] = Piece(PieceType::KING, Color::BLACK);

    return board;
}
