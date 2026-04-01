#pragma once
#include "Enums.h"
#include "Position.h"
#include "pch.h"

struct Move {
    Position from;
    Position to;
    MoveType moveType;
    Extra ex;

    Move(const Position& from, const Position& to, Extra ex = Extra::NONE);

    void isEnpassant() const;
    MoveType getMoveType() const;

    bool isMoveDouble(Color src) const;
    bool operator==(const Move& other) const;
};