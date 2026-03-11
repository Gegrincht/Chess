#include "ChessGame.h"
#include "Logger.h"

Position::Position(int x, int y)
	: x(x), y(y) {
	if (Helpers::outOfBoard(x, y)) {
		Log.tprefix("Position/Constructor").error("Position construction failed -- Position not inside board parameters.");
		throw std::out_of_range("Coordinates are out of board");
	}
}

bool Position::operator==(const Position& other) {
	return x == other.x && y == other.y;
}