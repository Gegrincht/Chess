#include "ChessGame.h"
#include "DefaultBoard.h"

ChessGame::ChessGame() : board(initDefaultBoard()) {} // do initializer list

bool ChessGame::movePiece(Move& move) {
    std::vector<Move> movesVector = generateMoves(board[move.fromX][move.fromY].color);
    auto it = std::find(movesVector.begin(), movesVector.end(), move);

    if (it == movesVector.end())
        return false;

    if (!board[move.fromX][move.fromY].exists()) return false;
    board[move.toX][move.toY] = board[move.fromX][move.fromY];
    board[move.fromX][move.fromY] = { PieceType::NONE, Color::NONE };
    return true;
}

bool ChessGame::movePiece(char fromX, int fromY, char toX, int toY) {
    int fx = Helpers::colCharToIndex(fromX);
    int tx = Helpers::colCharToIndex(toX);
    int fy = fromY - 1; // chess ys are 1-8, array is 0-7
    int ty = toY - 1;

    if (Helpers::outOfBoard(fx) || Helpers::outOfBoard(tx) || Helpers::outOfBoard(fy) || Helpers::outOfBoard(ty))
        return false; // invalid coordinates

    Move newMove(fx, fy, tx, ty);

    return movePiece(newMove); // call existing movePiece(int,int,int,int)
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

// Move Stuff

std::vector<Move> ChessGame::generateMoves(Color color) const { // calls every chess pieces moves and puts it all in a vector 
    std::vector<Move> generatedMoves;
    if (color == Color::NONE) return generatedMoves;

    generatedMoves.reserve(220);

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (board[x][y].color != color || board[x][y].type == PieceType::NONE)
                continue;
            std::vector<Move> vec = getMoves(x, y);
            generatedMoves.insert(generatedMoves.end(), vec.begin(), vec.end());
        }
    }
    return generatedMoves;
}

std::vector<Move> ChessGame::getMoves(int ix, int iy) const {
    if (Helpers::outOfBoard(ix, iy)) return {};
    const Piece& p = board[ix][iy];
    if (p.type == PieceType::NONE) return {};
    std::vector<Move> vec;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            const Move m(ix, iy, x, y);
            if (ix == x && iy == y)
                continue; // skip same square
            else if (isLegal(m))
                vec.push_back(m);
        }
    }
    return vec;
}



bool ChessGame::isLegal(const Move& move) const {
    const Piece& srcP = board[move.fromX][move.fromY];
    const Piece& tgtP = board[move.toX][move.toY];
    //Move inside board
    if (Helpers::outOfBoard(move.fromX, move.fromY) ||
        !srcP.exists() ||
        srcP.color == tgtP.color ||
        !pieceCanMoveLikeThat(move))
        // \|/
        return false;
    return true;
}