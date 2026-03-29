#include "pch.h"
#include "Chess.h"


Piece::Piece(PieceType giventype, Color givencolor)
    : type(giventype), color(givencolor), hasMoved(false), enPassantable(false) {
}

char Piece::getPieceIcon() const {
    char c;
    switch (type) {
    case PieceType::PAWN:   c = 'P'; break;
    case PieceType::ROOK:   c = 'R'; break;
    case PieceType::KNIGHT: c = 'N'; break;
    case PieceType::BISHOP: c = 'B'; break;
    case PieceType::QUEEN:  c = 'Q'; break;
    case PieceType::KING:   c = 'K'; break;
    default: c = '.'; break;
    }

    if (color == Color::BLACK)
        c = std::tolower(c);

    return c;
}

std::string Piece::getPieceName() const {
    std::string c;
    switch (type) {
    case PieceType::PAWN:   c = "PAWN"; break;
    case PieceType::ROOK:   c = "ROOK"; break;
    case PieceType::KNIGHT: c = "KNIGHT"; break;
    case PieceType::BISHOP: c = "BISHOP"; break;
    case PieceType::QUEEN:  c = "QUEEN"; break;
    case PieceType::KING:   c = "KING"; break;
    default: c = "None"; break;
    }
    if (color == Color::BLACK)
        Helpers::toLower(c);
    return c;
}

bool Piece::isColor(Color exColor) const {
    return (color == exColor);
}

bool Piece::exists() const {
    return (type != PieceType::NONE);
}