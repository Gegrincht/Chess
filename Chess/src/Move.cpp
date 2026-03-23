#include "ChessGame.h"
#include "Logger.h"

Move::Move(const Position& from, const Position& to, Extra ex)
    : from(from), to(to), moveType(getMoveType()), ex(ex) {

    if (!from.inBoard() || !to.inBoard())
        throw std::out_of_range("Move coordinates are out of board");
}

bool Move::isMoveDouble(Color src) const {
    int dir = (src == Color::WHITE) ? 1 : -1;
    if (moveType == MoveType::VERTICAL && from.y + (2 * dir) == to.y) {
        Log.tprefix("Test").warn(std::to_string(from.x) + "|" + std::to_string(from.y) + " -> " +
            std::to_string(to.x) + "|" + std::to_string(to.y) + " war erfolgreich.");
        return true;
    }
    if (from.y == 6 && from.x == 2 && to.x == 2 && to.y == 4)
        return false;
    else
        return false;
}

MoveType Move::getMoveType() const {
    int dx = abs(to.x - from.x);
    int dy = abs(to.y - from.y);

    if (!dx && dy)                                      return MoveType::VERTICAL;
    if (dx && !dy)                                      return MoveType::HORIZONTAL;
    if (dx == dy)                                       return MoveType::DIAGONAL;
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2))   return MoveType::LSHAPE;
    return MoveType::NONE;
}

bool Move::operator==(const Move& other) const {
    return from.x == other.from.x &&
        from.y == other.from.y &&
        to.x == other.to.x &&
        to.y == other.to.y;
}