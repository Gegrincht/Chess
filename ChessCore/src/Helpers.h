#pragma once
#include "pch.h"
#include "Piece.h"

namespace Helpers {
    void toLower(std::string& s);
    std::array<std::array<Piece, 8>, 8> initDefaultBoard();
}