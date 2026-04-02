#pragma once
#include "pch.h"

struct Position {
    int x;
    int y;

    Position() = default;
    Position(int x, int y);
    Position(char x, int y);

    bool operator==(const Position& other) const;

    int colCharToIndex(char col) const;
    bool inBoard() const;
};