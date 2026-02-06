#include "ChessGame.h"
#include "DefaultBoard.h"
#include <iostream>
#include <cstdlib>
#include <string>

Piece::Piece(PieceType giventype, Color givencolor)
	: type(giventype), color(givencolor) {}

Move::Move(Board& board, int ifromX, int ifromY, int itoX, int itoY)
    : fromX(ifromX), fromY(ifromY), toX(itoX), toY(itoY) { 

    if (outOfBoard(ifromX) ||
        outOfBoard(ifromY) ||
        outOfBoard(itoX) ||
        outOfBoard(itoY))
        throw std::out_of_range("Move coordinates are out of board");

    Piece& thisPiece = board[fromX][fromY];
    if (thisPiece.type == PieceType::NONE)
        allowedParty = Color::NONE;
    else { allowedParty = thisPiece.color; }
}


ChessGame::ChessGame() : board(initDefaultBoard()) {} // do initializer list

bool ChessGame::movePiece(int fromX, int fromY, int toX, int toY) {
    if (board[fromX][fromY].type != PieceType::NONE) {
        board[toX][toY] = board[fromX][fromY];
        board[fromX][fromY].type = PieceType::NONE;
        return true; } else { return false; }
}

bool ChessGame::movePiece(char fromX, int fromY, char toX, int toY) {
    int fx = colCharToIndex(fromX);
    int tx = colCharToIndex(toX);
    int fy = fromY - 1; // chess ranks are 1-8, array is 0-7
    int ty = toY - 1;

    if (outOfBoard(fx) || outOfBoard(tx) || outOfBoard(fy) || outOfBoard(ty))
        return false; // invalid coordinates

    return movePiece(fx, fy, tx, ty); // call existing movePiece(int,int,int,int)
}

Piece* ChessGame::getPieceAt(int x, int y)
{
    if (x < 0 || x > 7 || y < 0 || y > 7 || board[x][y].type == PieceType::NONE)
        return NULL;
    return &board[x][y];
}

Piece* ChessGame::getPieceAt(char x, int y)
{
    int intX = colCharToIndex(x);
    return getPieceAt(intX, y-1);
}

//Moves

std::vector<Move> ChessGame::generateMoves(Color color) {
    std::vector<Move> generatedMoves;
    for (int file = 0; file <= 7; file++) {
        for (int rank = 0; rank <= 7; rank++) {
            if (board[file][rank].color == color);
            std::vector<Move> x = getMoves(file, rank);
            generatedMoves.insert(generatedMoves.end(), x.begin(), x.end());
        }
    }

    return generatedMoves;
}

static int colCharToIndex(char col) {
    col = std::toupper(col);
    if (col < 'A' || col > 'H') return -1; // invalid
    return col - 'A'; // 'A'->0, 'B'->1, ..., 'H'->7
}

static bool outOfBoard(int x) {
    return x < 0 || x > 7;
}









int main() {
    ChessGame game;



    
    //while (1) {
        std::cout << "     A B C D E F G H\n  |-------------------|\n";
        for (int y = 7; y >= 0; --y) {      // print top to bottom
            std::cout << y + 1 << " |  ";
            for (int x = 0; x < 8; ++x) {
                char c = '.'; // empty square

                switch (game.board[x][y].type) {
                case PieceType::PAWN:   c = 'P'; break;
                case PieceType::ROOK:   c = 'R'; break;
                case PieceType::KNIGHT: c = 'N'; break;
                case PieceType::BISHOP: c = 'B'; break;
                case PieceType::QUEEN:  c = 'Q'; break;
                case PieceType::KING:   c = 'K'; break;
                default: c = '.'; break;
                }

                // optional: lowercase for black
                if (game.board[x][y].color == Color::BLACK)
                    c = std::tolower(c);

                std::cout << c << " ";
            }
            std::cout << " | " << y + 1 << "\n";
        }
        std::cout << "  |-------------------|\n     A B C D E F G H\n";
        /*
        std::string from, to;
        std::cout << "What to move: ";
        std::cin >> from >> to;

        int fromRow = from[1] - '0';
        int toRow = to[1] - '0';

        game.movePiece(from[0], fromRow, to[0], toRow);
        */
    //}
    std::string pos;

    std::cout << "Format ex: b2\nöwhat do you wanna get: ";
    std::cin >> pos;

    int row = pos[1] - '0';

    Piece myPiece = *game.getPieceAt(pos[0], row);

    
    char c = '.'; // empty square

    switch (myPiece.type) {
    case PieceType::PAWN:   c = 'P'; break;
    case PieceType::ROOK:   c = 'R'; break;
    case PieceType::KNIGHT: c = 'N'; break;
    case PieceType::BISHOP: c = 'B'; break;
    case PieceType::QUEEN:  c = 'Q'; break;
    case PieceType::KING:   c = 'K'; break;
    default: c = '.'; break;
    }

    // optional: lowercase for black
    if (myPiece.color == Color::BLACK)
        c = std::tolower(c);

    std::cout << c << " " << static_cast<int>(myPiece.type) << std::endl;
}