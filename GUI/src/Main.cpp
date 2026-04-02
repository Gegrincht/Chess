#include "Chess.h"
#include "../src/Logger.h"
#include <iostream>
#include <chrono>
#include <string>
#include <random>

std::string randomString(int length) {
    const std::string chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, chars.size() - 1);

    std::string result;
    for (int i = 0; i < length; ++i) {
        result += chars[dist(gen)];
    }

    return result;
}

void printBoard(ChessGame& game) {
    const bool isWhite = game.getCurrentPlayer() == Color::WHITE;
    std::cout << "To Move: " << (isWhite ? "White" : "Black") << "\n";

    int start = isWhite ? 7 : 0;
    int end = isWhite ? -1 : 8;
    int step = isWhite ? -1 : 1;
    char c;

    if (game.inCheck(game.getCurrentPlayer())) Log.warn("Current player is in Check.\n");

    std::cout << "     A B C D E F G H\n  |-------------------|\n";
    for (int y = start; y != end; y += step) {
        std::cout << y + 1 << " |  ";
        for (int x = 0; x < 8; ++x) {
            c = game.getPieceAt(Position(x, y))->getPieceIcon(' ');
            std::cout << c << " ";
        }
        std::cout << " | " << y + 1 << "\n";
    }
    std::cout << "  |-------------------|\n     A B C D E F G H\n";
}

void b_printBoard(ChessGame& game) {
    const bool isWhite = game.getCurrentPlayer() == Color::WHITE;
    std::cout << "To Move: " << (isWhite ? "White" : "Black") << "\n";

    int start = isWhite ? 7 : 0;
    int end = isWhite ? -1 : 8;
    int step = isWhite ? -1 : 1;

    if (game.inCheck(game.getCurrentPlayer()))
        Log.warn("Current player is in Check.\n");

    std::cout << "     ";
    if (isWhite) {
        for (char col = 'A'; col <= 'H'; ++col) std::cout << col << "  ";
    }
    else {
        for (char col = 'H'; col >= 'A'; --col) std::cout << col << "  ";
    }
    std::cout << "\n  |--------------------------|\n";

    for (int y = start; y != end; y += step) {
        std::cout << y + 1 << " | ";
        for (int x = 0; x < 8; ++x) {
            int drawX = isWhite ? x : 7 - x;
            const Piece* p = game.getPieceAt(Position(drawX, y));
            char c = p->getPieceIcon(' ');

            bool whiteSquare = (drawX + y) % 2 == 0;
            std::cout << (whiteSquare ? "\033[102m" : "\033[100m");

            if (p->color == Color::WHITE) std::cout << "\033[93m"; 
            else if (p->color == Color::BLACK) std::cout << "\033[30m"; 
            else std::cout << "\033[30m"; 

            std::cout << " " << c << " " << "\033[0m"; 
        }
        std::cout << " | " << y + 1 << "\n";
    }

    std::cout << "  |--------------------------|\n     ";
    if (isWhite) {
        for (char col = 'A'; col <= 'H'; ++col) std::cout << col << "  ";
    }
    else {
        for (char col = 'H'; col >= 'A'; --col) std::cout << col << "  ";
    }
    std::cout << "\n";
}

void benchmark(long int iterations = 10000) {
    long long total = 0;
    long long totalForPercent = 0;
    std::cout << "Press Enter to start test...";
    std::string line;
    std::getline(std::cin, line);

    // region BENCHMARK PREP
    
    Move m(Position('E', 2), Position('E', 4));
    
    // endregion BENCHMARK PREP END
    
    std::cout << "Starte Benchmark... \n";
    int lastPercent = 0;
    for (int i = 0; i < iterations; ++i) {
        ChessGame tgame;

        auto start = std::chrono::steady_clock::now();
        //BENCHMARK
        auto result = tgame.tryMove(m);
        auto end = std::chrono::steady_clock::now();
        std::ignore = result;

        auto tempTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        total += tempTime;
        totalForPercent += tempTime;

        int percent = (i * 100) / iterations;
        if (percent > lastPercent) {
            int iterationsInPercent = i - (lastPercent * iterations / 100);

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
    std::cout << "Average: " << (total / iterations) << "us\n";
    std::cout << "Total: " << (total / 1000.0) << "ms\n";
    std::cout << "Total Seconds: " << (total / 1000000.0) << "s\n";

    std::cout << "\n\n----------------------------------------\n\n";
}

int main() {
    ChessGame game;
    b_printBoard(game);

    for (int i = 0; i < 100; ++i) {
        std::string line;
        std::string from, to;
        std::cout << "What to move: ";
        std::getline(std::cin, line);
        std::istringstream iss(line);
        iss >> from >> to;

        int fromRow = from[1] - '0';
        int toRow = to[1] - '0';
        //std::cout << "\033[2J\033[H";
        if(!game.tryMove(Move(Position(from[0], fromRow), Position(to[0], toRow)))) Log.error("Illegal Move.");
        b_printBoard(game);
    }

    std::string randStr = randomString(2);
    std::cout << "Do you want to do a benchmark? If so type '" << randStr << "'. If the copied text is not exactly the same, program will close.\nPLEASE TYPE HERE: ";
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);

    std::string code;
    int number = 10000;

    iss >> code >> number;
    if (code == randStr) benchmark(number);
}