#include "ChessGame.h"
#include "DefaultBoard.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cctype>

/*
TODO LIST: ----------
* | make std::cout << format(Piece.type, "name") and "char" possible 
  | so you can print out the name of the piece or char

* | make legallity movement checks aka check if that piece can move this way and stuff
 
* | check if my moves sets my king in check or if my king is in still in 
  | check if i do my next move

* | impliment following methods:
  -> getMoves(char file, int rank); & getMoves(Piece curPiece);
  -> isInCheck(Color color);
  -> wouldBeInCheckAfterMove(const& Move)
*/

// ------------------------
// ===== Piece Class ======
// ------------------------

Piece::Piece(PieceType giventype, Color givencolor)
	: type(giventype), color(givencolor) {}

char Piece::getPieceIcon() const {
    char c;
    switch (type) {
    case PieceType::PAWN:   c = 'P'; break;
    case PieceType::ROOK:   c = 'R'; break;
    case PieceType::KNIGHT: c = 'N'; break;
    case PieceType::BISHOP: c = 'B'; break;
    case PieceType::QUEEN:  c = 'Q'; break;
    case PieceType::KING:   c = 'K'; break;
    default: c = '.'; break;
    }

    if (color == Color::BLACK)
        c = std::tolower(c);

    return c;
}

std::string Piece::getPieceName() const {
    std::string c;
    switch (type) {
    case PieceType::PAWN:   c = "PAWN"; break;
    case PieceType::ROOK:   c = "ROOK"; break;
    case PieceType::KNIGHT: c = "KNIGHT"; break;
    case PieceType::BISHOP: c = "BISHOP"; break;
    case PieceType::QUEEN:  c = "QUEEN"; break;
    case PieceType::KING:   c = "KING"; break;
    default: c = "None"; break;
    }
    if (color == Color::BLACK)
        toLower(c);
    return c;
}

// -----------------------
// ===== Move Class ======
// -----------------------

Move::Move(Board& board, unsigned int ifromX, unsigned int ifromY, unsigned int itoX, unsigned int itoY)
    : fromX(ifromX), fromY(ifromY), toX(itoX), toY(itoY) { 

    if (outOfBoard(ifromX) || outOfBoard(ifromY) ||
        outOfBoard(itoX) || outOfBoard(itoY))
        throw std::out_of_range("Move coordinates are out of board");

    Piece& thisPiece = board[fromX][fromY];
    allowedParty = (thisPiece.type == PieceType::NONE) ? Color::NONE : thisPiece.color;
}

// ----------------------------
// ===== Chessgame Class ======
// ----------------------------

ChessGame::ChessGame() : board(initDefaultBoard()) {} // do initializer list

bool ChessGame::movePiece(Move move) {
    if (board[move.fromX][move.fromY].type == PieceType::NONE) return false; 
    board[move.toX][move.toY] = board[move.fromX][move.fromY];
    board[move.fromX][move.fromY] = {PieceType::NONE, Color::NONE};
    return true;
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
    if (x < 0 || x > 7 || y < 0 || y > 7)
        return NULL;
    return &board[x][y];
}

Piece* ChessGame::getPieceAt(char x, int y)
{
    int intX = colCharToIndex(x);
    return getPieceAt(intX, y-1);
}

// Move Stuff

std::vector<Move> ChessGame::generateMoves(Color color) const { // calls every chess pieces moves and puts it all in a vector 
    std::vector<Move> generatedMoves;
    if (color == Color::NONE) return generatedMoves;

    generatedMoves.reserve(220);

    for (int file = 0; file <= 7; file++) {
        for (int rank = 0; rank <= 7; rank++) {
            if (board[file][rank].color != color || board[file][rank].type == PieceType::NONE)
                continue;
            std::vector<Move> x = getMoves(file, rank);
            generatedMoves.insert(generatedMoves.end(), x.begin(), x.end());
        }
    }
    return generatedMoves;
}

std::vector<Move> ChessGame::getMoves(int x, int y) const {
    return std::vector<Move>{};
}


// Static Methods

static int colCharToIndex(char col) {
    col = std::toupper(col);
    if (col < 'A' || col > 'H') return -1; // invalid
    return col - 'A'; // 'A'->0, 'B'->1, ..., 'H'->7
}

static bool outOfBoard(int x) {
    return x < 0 || x > 7;
}

static void toLower(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {return std::tolower(c); });
}







// TESTING SPECIFIC FUNTIONS



void printBoard(ChessGame& game) {
    std::cout << "     A B C D E F G H\n  |-------------------|\n";
    for (int y = 7; y >= 0; --y) {      // print top to bottom
        std::cout << y + 1 << " |  ";
        for (int x = 0; x < 8; ++x) {
            char c = game.board[x][y].getPieceIcon();

            std::cout << c << " ";
        }
        std::cout << " | " << y + 1 << "\n";
    }
    std::cout << "  |-------------------|\n     A B C D E F G H\n";
}



int main() {
    ChessGame game;

    printBoard(game);

    //while (1) {
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

    std::cout << "Format ex: b2\nwhat do you wanna get: ";
    std::cin >> pos;

    int row = pos[1] - '0';

    Piece myPiece = *game.getPieceAt(pos[0], row);

    
    const char c = myPiece.getPieceIcon();

    const std::string name = myPiece.getPieceName();

    std::string color;
    switch (myPiece.color)
    {
        case Color::WHITE:
            color = "White"; break;
        case Color::BLACK:
            color = "Black"; break;
        default:
            color = "None";  break;
    }

    std::cout << "PieceIcon: " << c << 
        "\nPieceName: " << color << " " << name << 
        "\nTypeValue: " << static_cast<int>(myPiece.type) << 
        std::endl;
}