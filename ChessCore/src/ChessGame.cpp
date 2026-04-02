#include "pch.h"
#include "Logger.h"
#include "ChessGame.h"
#include "Helpers.h"
#include "Position.h"
#include "DefaultBoard.h"

ChessGame::ChessGame() : board(Helpers::initDefaultBoard()) { afterMoveHandler(); }

const Color ChessGame::getCurrentPlayer() const {
    return toMove;
}

void ChessGame::afterMoveHandler() {
    curMoves = generateMoves(toMove);

    if (curMoves.empty()) {
        if (inCheck(toMove)) {
            //Checkmate
            Log.warn("GAME OVER - Checkmate. ", (toMove == Color::WHITE) ? "Black" : "White", " won the game!");
        }
        else {
            //Stalemate
            Log.warn("GAME OVER - Stalemate. ", (toMove == Color::WHITE) ? "White" : "Black", " can't move anymore.");
        }
    }
}

bool ChessGame::tryMove(const Move& move) {
    if (board[move.from.x][move.from.y].color != toMove) return false;
    auto it = std::find(curMoves.begin(), curMoves.end(), move);
    if (it == curMoves.end())
        return false;

    const int dir = board[move.from.x][move.from.y].color == Color::WHITE ? 1 : -1;
    if (board[move.from.x][move.from.y].type == PieceType::PAWN && board[move.to.x][move.to.y].enPassantable && board[move.to.x][move.to.y - dir].type == PieceType::PAWN) board[move.to.x][move.to.y - dir] = {PieceType::NONE, Color::NONE};
    
    //pass
    switchTurnColor(Color::NONE);
    enPassantReset();
    if (it->ex == Extra::DOUBLE) board[(move.to.x + move.from.x) / 2][(move.to.y + move.from.y) / 2].enPassantable = true;
    board[move.from.x][move.from.y].hasMoved = true;
    board[move.to.x][move.to.y] = board[move.from.x][move.from.y];
    board[move.from.x][move.from.y] = { PieceType::NONE, Color::NONE };

    afterMoveHandler();
    return true;
}

void ChessGame::enPassantReset() {
    forEachSquare([&](const Position& pos) {
        board[pos.x][pos.y].enPassantable = false;
    });
}

bool ChessGame::tryMove(const Position& from, const Position& to) {
    const Move mv = Move(from, to);
    return tryMove(mv);
}

const Piece* ChessGame::getPieceAt(const Position& pos) const
{
    if (!pos.inBoard()) return nullptr;
    return &board[pos.x][pos.y];
}

void ChessGame::clearBoard() {
    board = std::array<std::array<Piece, 8>, 8>();
}

void ChessGame::resetBoard() {
    board = Helpers::initDefaultBoard();
}

void ChessGame::switchTurnColor(Color next = Color::NONE) {
    if (next == Color::NONE) toMove = (toMove == Color::WHITE) ? Color::BLACK : Color::WHITE;
    else toMove = next;
}

void ChessGame::setPiece(const Position& pos, const Piece& p) {
    board[pos.x][pos.y] = p;
}

bool ChessGame::inCheck(Color color) const {
    Position kingPos;
    forEachSquare([&](const Position& pos) {
        if (board[pos.x][pos.y].type == PieceType::KING && board[pos.x][pos.y].color == color)
            kingPos = pos;
        });

    bool check = false;
    Move m(Position(0, 0), kingPos);
    forEachSquare([&](const Position& pos) {
        const Piece& p = board[pos.x][pos.y];
        if (p.color != color && p.exists()) {
            m.from = pos;
            if (pieceCanMoveLikeThat(m)) check = true;
        }
    });
    return check;
}

bool ChessGame::wouldBeInCheckAfterMove(const Move& move) {
    const Piece fromPiece = board[move.from.x][move.from.y];
    const Piece toPiece = board[move.to.x][move.to.y];

    // Temporär move ausführen
    board[move.to.x][move.to.y] = fromPiece;
    board[move.from.x][move.from.y] = { PieceType::NONE, Color::NONE };

    bool check = inCheck(fromPiece.color);

    // Move rückgängig machen
    board[move.from.x][move.from.y] = fromPiece;
    board[move.to.x][move.to.y] = toPiece;

    return check;
}