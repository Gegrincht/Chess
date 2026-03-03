# MakingChess

## Short description
This project implements the core logic for a chess engine focused on move generation and move legality checks. Current focus areas:
- clean move generators
- verifying that moves do not leave the player's king in check
- human-readable `Piece` output (name / icon)
- integration with OpenGL for windowing/rendering

## Current status
- [x] Core types for `Board`, `Piece` and `Move` exist
- [x] `Piece::getPieceIcon()` and `Piece::getPieceName()` implemented
- [x] Basic `movePiece` (index and char overload) implemented
- [x] `getPieceAt(int,int)` and `getPieceAt(char,int)` implemented
- [x] Helper functions `Helpers::colCharToIndex`, `Helpers::outOfBoard`, `toLower` implemented
- [x] `generateMoves(Color)` calls `getMoves` per piece
- [x] `printBoard` test helper and a simple `main` test stub exist

Many checks for move legality are still missing or incomplete.

## isLegal To-Do list

- [x] Check that move is inside the board
  - Verify that `move.toX` and `move.toY` are within 0–7
  - Helper: `bool Helpers::outOfBoard(int x, int y);`

- [x] Check that the source square has a piece
  - Verify that a piece exists at `move.fromX, move.fromY`
  - Helper: `bool isEmpty(int x, int y);`

- [x] Check that target square is not occupied by same color
  - Ensure the target is not occupied by a friendly piece
  - Helper: `bool isEnemy(int x, int y, Color ownColor);`

- [ ] Check if the piece can move in that way (geometric rules)
  - Helper: `bool pieceCanMoveLikeThat(const Move& move);`
  - Considerations:
    - [ ] Rook → straight lines
    - [ ] Bishop → diagonals
    - [ ] Queen → rook + bishop movements
    - [ ] Knight → L-shape
    - [ ] King → single-square moves + castling
    - [ ] Pawn → single move, double move, diagonal captures, en passant

    - [ ] Path blocking for sliding pieces (rook, bishop, queen)
      - Verify that sliding pieces are not blocked by any piece along their path

- [ ] Handle special moves
  - [ ] Castling
    - King & corresponding rook must not have moved
    - No pieces between King & rook
    - King must not currently be in check
    - King must not pass through an attacked square
    - Tracking variables: `whiteKingMoved, blackKingMoved, whiteRookAMoved, whiteRookHMoved, ...`
  - [ ] En passant <- THIS IN `bool pieceCanMoveLikeThat(const Move& move);`
    - Pawn can capture en passant when `enPassantTarget` is set
    - Update `enPassantTarget` after a double pawn move
    - Helper variable example: `std::optional<std::pair<int,int>> enPassantTarget;`
  - [ ] Pawn promotion
    - Can be handled separately for UI; affects move legality only insofar as the move is allowed

- [ ] Simulate the move and check king safety
  - Temporarily apply the move
  - Verify whether own king would be in check afterwards
  - Helper: `bool wouldBeInCheckAfterMove(const Move& move);`

- [ ] Implement helper `inCheck(Color color)`
  - Determine whether the king of the given color is currently in check
  - Check all opponent pseudo-legal moves (without king-safety)
  - Used by `wouldBeInCheckAfterMove`

- [ ] Maintain castling rights state
  - `bool whiteKingMoved, blackKingMoved`
  - `bool whiteRookAMoved, whiteRookHMoved, blackRookAMoved, blackRookHMoved`

- [ ] Maintain en passant target state
  - Set after a pawn double-step
  - Clear after the next move

- [ ] Final `isLegal` return
  - Return `true` if all checks pass, otherwise `false`

## Short TODO list
- [ ] Accept character input for public methods to allow inputs like "B2"
- [ ] Implement or verify utility methods:
  - [x] `bool isEmpty(int x, int y);` — check whether a square is empty
  - [x] `bool isEnemy(int x, int y, Color ownColor);` — check whether a square contains an enemy piece
  - [x] `bool Helpers::outOfBoard(int x, int y)` — 2D version of `Helpers::outOfBoard(int x)`
  - [x] `std::vector<Move> getMoves(char file, int rank);` — enumerate possible moves for a piece
    - For each candidate move, call `isLegal` and add it to the vector if valid
  - [ ] `bool inCheck(Color color);` — check if the specified color is in check
  - [ ] `bool isSquareAttacked(int x, int y, Color ownColor);` — check if a square is attacked by the opponent
  - [ ] `bool wouldBeInCheckAfterMove(const Move& move);` — simulate a move and return the result using `inCheck`
  - [ ] `bool isLegal(const Move& move) const;` — orchestrate all legality checks

Note: In `getMoves` candidate moves should be simulated and those that leave the king in check should be skipped using `continue` (see `.github/copilot-instructions.md`).

## Extended TODO list

Core logic
- [ ] Fully implement special moves:
  - [ ] Castling (king/rook unmoved, clear path, no check on path)
  - [ ] En passant (validation and undo)
  - [ ] Pawn promotion (selection and replacement)
- [ ] Draw / game-end checks:
  - [ ] Checkmate & stalemate detection
  - [ ] Insufficient material, 50-move rule, threefold repetition
- [ ] Correct board state management:
  - [ ] Move history, `undo()` / `redo()`
  - [ ] Reversible vs irreversible state (e.g. en-passant, castling rights)

Engine / search (optional)
- [ ] Time management / time controls

UI & UX
- [ ] Input methods:
  - [ ] Click-to-move, drag-and-drop, keyboard shortcuts
  - [ ] Visual feedback: highlight legal moves, last move, check
- [ ] Debug overlay: board dumps, move logs, performance counters
- [ ] Responsive window/resize handling (viewport / aspect ratio for OpenGL)

Prioritization suggestion
1. Complete `getMoves` + simulation (`wouldBeInCheckAfterMove`) + unit tests (PERFT)
2. Special moves (castling, en passant, promotion)
3. `isInCheck` & game-end checks (checkmate/stalemate)
4. Undo/redo
5. Basic engine (alpha-beta) + performance optimizations
6. UI

## Short development plan
1. Correctly implement `getMoves` for every piece (including special moves)
2. Add simulation routine to determine `wouldBeInCheckAfterMove`
3. Stabilize `inCheck` and integrate it into move filtering

## Build / Run
- Open the project in Visual Studio 2022+ (`.sln` / `.vcxproj`)
- Dependencies: OpenGL (GLEW/GLFW or custom setup) — see the `Dependecies` folder
- Recommended build configuration: __Debug__ / __x64__

---------------

Note: This README was drafted with AI assistance.
