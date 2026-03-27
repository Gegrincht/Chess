#include "ChessGame.h"
#include <iostream>
#include <string>
#include "Logger.h"
#include <chrono>

// TESTING SPECIFIC FUNTIONS. IGNORE FOR MAKING GAME CLASSES

void printBoard(ChessGame& game) {
    std::cout << "     A B C D E F G H\n  |-------------------|\n";
    for (int y = 7; y >= 0; --y) {      // print top to bottom
        std::cout << y + 1 << " |  ";
        for (int x = 0; x < 8; ++x) {
            char c = game.getPieceAt(Position(x, y))->getPieceIcon();
            std::cout << c << " ";
        }
        std::cout << " | " << y + 1 << "\n";
    }
    std::cout << "  |-------------------|\n     A B C D E F G H\n";
}

void benchmark(long int ITERATIONS) {
    long long total = 0;
    long long totalForPercent = 0;
    std::cout << "Press Enter to start test...";
    std::string line;
    std::getline(std::cin, line);

    //BENCHMARK PREP
    Move m(Position('E', 2), Position('E', 4));

    std::cout << "Starte Benchmark... \n";
    int lastPercent = 0;
    for (int i = 0; i < ITERATIONS; ++i) {
        ChessGame tgame;

        auto start = std::chrono::steady_clock::now();
        //BENCHMARK
        auto result = tgame.tryMove(m);
        auto end = std::chrono::steady_clock::now();
        std::ignore = result;

        auto tempTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        total += tempTime;
        totalForPercent += tempTime;

        int percent = (i * 100) / ITERATIONS;
        if (percent > lastPercent) {
            int iterationsInPercent = i - (lastPercent * ITERATIONS / 100);

            std::cout << "\033[2K\r" << std::chrono::system_clock::now() << " |---| " << percent << "%\n";
            std::cout << "\033[2K\rProgress\t: " << i << "\n";
            std::cout << "\033[2K\rCurrent Average\t: " << (total / (i + 1.0)) << "us\n";
            std::cout << "\033[2K\rAverage this 1%\t: " << (totalForPercent / (iterationsInPercent * 1.0)) << "us\n";
            std::cout << "\033[4A" << std::flush;

            totalForPercent = 0;
            lastPercent = percent;
        }
    }
    std::cout << "\033[2J\033[H" << std::flush;
    std::cout << "Average: " << (total / ITERATIONS) << "us\n";
    std::cout << "Total: " << (total / 1000.0) << "ms\n";
    std::cout << "Total Seconds: " << (total / 1000000.0) << "s\n";

    std::cout << "\n\n----------------------------------------\n\n";
}

int main() {
    benchmark(10000);
    
    ChessGame game;
    /*
    game.tryMove(Position('B', 2), Position('B', 4));
    game.tryMove(Position('B', 4), Position('B', 5));
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    game.tryMove(Position('C', 7), Position('C', 5));
    std::cout << game.board[2][5].enPassantable << std::endl;
    */
    //game.clearBoard();
    game.setPiece(Position('C', 3), Piece(PieceType::BISHOP, Color::WHITE));

    printBoard(game);
    while (1) {
        
        std::string from, to;
        std::cout << "What to move: ";
        std::cin >> from >> to;

        int fromRow = from[1] - '0';
        int toRow = to[1] - '0';
        //Position(from[0], fromRow);
        //Position(to[0], toRow);
        if (!game.tryMove(Position(from[0], fromRow), Position(to[0], toRow))) Log.error("Piece can't move to that location");

        printBoard(game);
    }
    
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
