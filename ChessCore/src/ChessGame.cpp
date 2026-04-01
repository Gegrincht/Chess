#include "pch.h"
#include "ChessGame.h"
#include "Helpers.h"
#include "Position.h"
#include "DefaultBoard.h"

ChessGame::ChessGame() : board(Helpers::initDefaultBoard()) {}

bool ChessGame::tryMove(const Move& move) {
    std::vector<Move> movesVector = generateMoves(board[move.from.x][move.from.y].color);
    auto it = std::find(movesVector.begin(), movesVector.end(), move);
    if (it == movesVector.end())
        return false;

    const int dir = board[move.from.x][move.from.y].color == Color::WHITE ? 1 : -1;
    if (board[move.from.x][move.from.y].type == PieceType::PAWN && board[move.to.x][move.to.y].enPassantable && board[move.to.x][move.to.y - dir].type == PieceType::PAWN) board[move.to.x][move.to.y - dir] = {PieceType::NONE, Color::NONE};
    
    enPassantReset();
    
    if (it->ex == Extra::DOUBLE) board[(move.to.x + move.from.x) / 2][(move.to.y + move.from.y) / 2].enPassantable = true;
    board[move.from.x][move.from.y].hasMoved = true;
    board[move.to.x][move.to.y] = board[move.from.x][move.from.y];
    board[move.from.x][move.from.y] = { PieceType::NONE, Color::NONE };
    return true;
}

void ChessGame::enPassantReset() {
    forEachSquare([&](const Position& pos) {
        board[pos.x][pos.y].enPassantable = false;
    });
}

bool ChessGame::tryMove(const Position& from, const Position& to) {
    const Move mv = Move(from, to);
    return tryMove(mv);
}

const Piece* ChessGame::getPieceAt(const Position& pos) const
{
    if (!pos.inBoard()) return nullptr;
    return &board[pos.x][pos.y];
}

void ChessGame::clearBoard() {
    board = std::array<std::array<Piece, 8>, 8>();
}

void ChessGame::resetBoard() {
    board = Helpers::initDefaultBoard();
}

void ChessGame::switchTurnColor(Color next = Color::NONE) {
    if (next == Color::NONE) next = (toMove == Color::WHITE) ? Color::BLACK : Color::WHITE;
    toMove = next;
}

void ChessGame::setPiece(const Position& pos, const Piece& p) {
    board[pos.x][pos.y] = p;
}