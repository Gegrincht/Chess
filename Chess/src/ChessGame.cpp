#include "ChessGame.h"
#include "DefaultBoard.h"

ChessGame::ChessGame() : board(initDefaultBoard()) {} // do initializer list

bool ChessGame::tryMove(const Move& move) {
    std::vector<Move> movesVector = generateMoves(board[move.from.x][move.from.y].color);
    auto it = std::find(movesVector.begin(), movesVector.end(), move);

    if (it == movesVector.end())
        return false;
    if (!board[move.from.x][move.from.y].exists()) return false;
    enPassantReset();
    if (it->ex == Extra::DOUBLE) board[(move.to.x + move.from.x) / 2][(move.to.y + move.from.y) / 2].enPassantable = true;
    board[move.from.x][move.from.y].hasMoved = true;
    board[move.to.x][move.to.y] = board[move.from.x][move.from.y];
    board[move.from.x][move.from.y] = { PieceType::NONE, Color::NONE };
    if (board[move.from.x][move.from.y].enPassantable <------ - WORK HERE ON HERE WITH GET DIRECTION OF OTHER COLOR AND DELETE PIECE IN THAT DIRECTION );
    return true;
}

void ChessGame::enPassantReset() {
    forEachSquare([&](Position pos) {
        board[pos.x][pos.y].enPassantable = false;
        });
}

bool ChessGame::tryMove(const Position& from, const Position& to) {
    const Move mv = Move(from, to);
    return tryMove(mv); // call existing movePiece(int,int,int,int)
}

const Piece* ChessGame::getPieceAt(const Position& pos) const
{
    if (!pos.inBoard()) return nullptr;
    return &board[pos.x][pos.y];
}