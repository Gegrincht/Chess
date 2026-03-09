#include "ChessGame.h"
#include <iostream>
#include <string>

// TESTING SPECIFIC FUNTIONS. IGNORE FOR MAKING GAME CLASSES

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
    
    /*Move m(0, 1, 0, 2);

    //game.whiteMoves.push_back(Move(0, 1, 0, 2));
    game.whiteMoves.push_back(Move(0, 1, 0, 3));
    game.whiteMoves.push_back(Move(0, 1, 0, 4));
    game.whiteMoves.push_back(Move(0, 1, 0, 5));

    auto it = std::find(game.whiteMoves.begin(), game.whiteMoves.end(), m);

    std::cout << ((it != game.whiteMoves.end()) ? "True: Move m is in whiteMoves" : "False: Move m is NOT in whiteMoves");*/
    
    std::cin.get();

    /*std::string pos;

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
        std::endl;*/
}
