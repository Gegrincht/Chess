#include "ChessGame.h"
#include <iostream>
#include <algorithm>
#include <locale>

void Helpers::logInfo(const std::string& text){
    std::cout << GREEN << "[INFO] " << RESET << text << std::endl;
}

void Helpers::logWarn(const std::string& text){
    std::cout << YELLOW << "[WARN] " << RESET << text << std::endl;
}

void Helpers::logError(const std::string& text){
    std::cout << RED << "[ERROR] " << RESET << text << std::endl;
}


int Helpers::colCharToIndex(char col) {
    col = std::toupper(col);
    if (col < 'A' || col > 'H') return -1; // invalid
    return col - 'A'; // 'A'->0, 'B'->1, ..., 'H'->7
}

bool Helpers::outOfBoard(int x) {
    return x < 0 || x > 7;
}
bool Helpers::outOfBoard(int x, int y) {
    return x < 0 || x > 7 || y < 0 || y > 7;
}

void Helpers::toLower(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) { return std::tolower(c); });
}