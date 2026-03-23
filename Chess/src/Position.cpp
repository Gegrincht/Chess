#include "ChessGame.h"
#include "Logger.h"

/// <summary>
/// Initializes a Position with specified x and y coordinates and throws std::out_of_range
/// if the coordinates are outside the board parameters.
/// </summary>
/// <param name="x">0-based column index (0..7).</param>
/// <param name="y">0-based row index (0..7).</param>
Position::Position(int x, int y)
	: x(x), y(y) {
	if (!inBoard()) {
		Log.tprefix("Position/Constructor").error("Position construction failed -- Position not inside board parameters.");
		throw std::out_of_range("Coordinates are out of board");
	}
}

/// <summary>
/// Takes Char for x and Int for y and makes them into indexes that can be used to create array coordinates.
/// </summary>
/// <param name="x">char input of a Chessboard.</param>
/// <param name="y">int input to be used with numerated number on Chessboard. For example: 1 -> 0, 5 -> 4</param>
Position::Position(char x, int y)
	: x(colCharToIndex(x)), y(y-1) {
	if (!inBoard()) {
		Log.tprefix("Position/Constructor").error("Position construction failed -- Position not inside board parameters.");
		throw std::out_of_range("Coordinates are out of board");
	}
}

int Position::colCharToIndex(char col) const {
	col = std::toupper(col);
	if (col < 'A' || col > 'H') {
		Log.tprefix("Position/colCharToIndex").error("Failed to convert char to int. Char is not 'A' <= char <= 'H'");
		throw std::out_of_range("Failed to convert char to int. Coordinates are out of Chessboard");
	}
	return col - 'A';
}

bool Position::inBoard() const {
	return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}

bool Position::operator==(const Position& other) {
	return x == other.x && y == other.y;
}