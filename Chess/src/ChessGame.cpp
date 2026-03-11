#include "ChessGame.h"
#include "DefaultBoard.h"

ChessGame::ChessGame() : board(initDefaultBoard()) {} // do initializer list

bool ChessGame::tryMove(Move& move) {
    std::vector<Move> movesVector = generateMoves(board[move.from.x][move.from.y].color);
    auto it = std::find(movesVector.begin(), movesVector.end(), move);

    if (it == movesVector.end())
        return false;

    if (!board[move.from.x][move.from.y].exists()) return false;
    board[move.to.x][move.to.y] = board[move.from.x][move.from.y];
    board[move.from.x][move.from.y] = { PieceType::NONE, Color::NONE };
    return true;
}

bool ChessGame::tryMove(char ifx, int ify, char itx, int ity) {
    int fx = Helpers::colCharToIndex(ifx);
    int tx = Helpers::colCharToIndex(itx);
    int fy = ify - 1; // chess ys are 1-8, array is 0-7
    int ty = ity - 1;

    if (Helpers::outOfBoard(fx) || Helpers::outOfBoard(tx) || Helpers::outOfBoard(fy) || Helpers::outOfBoard(ty))
        return false; // invalid coordinates

    Move newMove(fx, fy, tx, ty);

    return tryMove(newMove); // call existing movePiece(int,int,int,int)
}

const Piece* ChessGame::getPieceAt(int x, int y) const
{
    if (Helpers::outOfBoard(x, y)) return nullptr;
    return &board[x][y];
}

const Piece* ChessGame::getPieceAt(char x, int y) const
{
    int intX = Helpers::colCharToIndex(x);
    return getPieceAt(intX, y - 1);
}