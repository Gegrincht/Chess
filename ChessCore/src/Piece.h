#pragma once
#include "pch.h"
#include "Enums.h"

struct Piece {
    PieceType type = PieceType::NONE;
    Color color = Color::NONE;
    bool hasMoved = false;
    bool enPassantable = false;

    Piece() = default;
    Piece(PieceType giventype, Color givencolor);

    char getPieceIcon(const char def = '.') const;
    std::string getPieceName() const;

    bool isColor(Color exColor) const;
    bool exists() const;

    bool operator==(const Piece& other);
};