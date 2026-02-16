# MakingChess

## Kurzbeschreibung
Ich arbeite daran, eine robuste Zug-Generierung und Legality-Überprüfung zu implementieren. Der Fokus liegt aktuell auf:
- sauberen Move-Generatoren,
- Prüfung, ob Züge den eigenen König in Schach lassen,
- menschenlesbarer Ausgabe von `Piece`-Informationen (Name / Zeichen),
- Integration mit OpenGL für Fenster/Rendering.

## Aktueller Status
- [x] ~~Grundstrukturen für `Board`, `Piece` und `Move` vorhanden.~~  
- [x] ~~`Piece::getPieceIcon()` und `Piece::getPieceName()` implementiert (Icon & Name verfügbar).~~  
- [x] ~~Basis-`movePiece` (Index- und char-Overload) implementiert.~~  
- [x] ~~`getPieceAt(int,int)` und `getPieceAt(char,int)` implementiert.~~  
- [x] ~~Hilfsfunktionen `colCharToIndex`, `outOfBoard`, `toLower` vorhanden.~~  
- [x] ~~`generateMoves(Color)` ruft `getMoves` pro Figur auf (aktuell liefert `getMoves` noch keine Züge).~~  
- [x] ~~`printBoard` Test-Helper + einfache `main`-Test-Stub vorhanden.~~

Viele Prüfungen zur Zuglegitimität fehlen noch oder sind unvollständig.

# isLegal ToDo Liste

- [x] check if move is inside board
    - Prüfe, ob `move.toX` und `move.toY` innerhalb 0–7 liegen
    - Hilfsfunktion: `bool outOfBoard(int x, int y);`

- [x] check if from-square has a piece
    - Prüfe, ob auf `move.fromX, move.fromY` ein Piece existiert
    - Hilfsfunktion: `bool isEmpty(int x, int y);`

- [x] check if target square is not same color
    - Stelle sicher, dass das Ziel nicht von einem eigenen Piece belegt ist
    - Hilfsfunktion: `bool isEnemy(int x, int y, Color ownColor);`

- [ ] check if the piece can move like that
    - Prüft, ob die Bewegung geometrisch korrekt ist für das Piece
    - Hilfsfunktion: `bool pieceCanMoveLikeThat(const Move& move);`
    - Muss berücksichtigen:
        - [ ] Rook → gerade Linien
        - [ ] Bishop → Diagonale
        - [ ] Queen → Rook + Bishop
        - [ ] Knight → L-Form
        - [ ] King → 1 Feld + Castling
        - [ ] Pawn → 1 Feld, 2 Felder, diagonales Capture, en passant

        - [ ] check for path blocking for sliding pieces
            - Prüft, ob Rook, Bishop, Queen auf ihrem Weg nicht von eigenen oder gegnerischen Figuren blockiert werden

- [ ] handle special moves
    - [ ] castling
        - King & Rook dürfen noch nicht bewegt sein
        - Keine Felder zwischen King & Rook
        - King darf aktuell nicht im Schach stehen
        - King darf kein Feld auf dem Weg angegriffen sein
        - Hilfsvariablen: `whiteKingMoved, blackKingMoved, whiteRookAMoved, whiteRookHMoved, ...`
    - [ ] en passant
        - Pawn darf diagonal ziehen, wenn `enPassantTarget` gesetzt ist
        - Nach Zug muss `enPassantTarget` korrekt aktualisiert werden
        - Hilfsvariable: `std::optional<std::pair<int,int>> enPassantTarget;`
    - [ ] pawn promotion
        - Optional für Zug-Gültigkeit, später für UI/Upgrade

- [ ] simulate move and check king safety
    - Simuliere den Zug temporär
    - Prüfe, ob eigener König danach im Schach steht
    - Hilfsfunktion: `bool wouldBeInCheckAfterMove(const Move& move);`

- [ ] implement helper inCheck(Color color)
    - Prüft, ob der König der angegebenen Farbe aktuell im Schach steht
    - Alle gegnerischen pseudo-legale Züge prüfen (ohne King-Safety)
    - Wird von `wouldBeInCheckAfterMove` genutzt

- [ ] maintain state for castling rights
    - bool `whiteKingMoved, blackKingMoved`
    - bool `whiteRookAMoved, whiteRookHMoved, blackRookAMoved, blackRookHMoved`

- [ ] maintain state for en passant target
    - Setzen nach Doppelzug eines Pawns
    - Zurücksetzen nach dem nächsten Zug

- [ ] final isLegal return
    - Wenn alle Prüfungen bestanden: return true
    - Sonst: return false

# TODO-Liste (Kurz)
- [ ] Für Public Methoden Char eingaben akzeptieren um Inputs wie "B2" zu erlauben.
- [ ] Implementiere folgende Methoden:
  - [x] `bool isEmpty(int x, int y);`
    - Prüfe ob feld Leer ist.
  - [x] `bool isEnemy(int x, int y, Color ownColor);`
    - Prüfe ob im Feld ein gegner ist.
  - [x] `bool outOfBoard(int x, int y)`
    - 2D version vom `outOfBoard(int x);` was schon implimentiert ist.
  - [x] `std::vector<Move> getMoves(char file, int rank);`
    - Gehe durch jedes Piece und berechne jeden möglichen Zug.
    - Für jeden möglichen Zug wird `isLegal` aufgerufen & wenn true:
      - wird der Zug zur Vektor-Liste hinzugefügt
    - nachdem alle theoretisch möglichen Züge durchgegangen wurden (z. B.: von B2 nach A1, A2, A3 usw. – für jedes Feld auf dem Brett wird isLegal aufgerufen)
  - [ ] `bool inCheck(Color color);`
    - Prüft, ob der König der angegebenen Farbe im Schach steht.
  - [ ] `isSquareAttacked(int x, int y, Color ownColor)`
    - Prüft ob ein Feld vom gegner Attackiert wird. 
  - [ ] `bool wouldBeInCheckAfterMove(const Move& move);`
    - Simuliert den Zug
    - gibt das Ergebnis von `inCheck` zurück
  - [ ] `bool isLegal(const Move& move) const;`
    - Prüft, ob ein Zug legal ist, indem Folgendes aufgerufen wird:
      - `wouldBeInCheckAfterMove`
      - Prüft, ob das Piece sich so bewegen darf
      - andere Bedingungen, die den Zug verhindern könnten
    - Wenn irgendeine Bedingung den Zug unmöglich macht, wird einfach 0 zurückgegeben

Hinweis: Bei `getMoves` sollen Züge durch Simulieren angewendet und solche, die den König in Schach lassen, mit `continue` übersprungen werden (siehe Projektvorgabe in `.github/copilot-instructions.md`).

## Erweiterte TODO-Liste

Core-Logik
- [ ] Sonderzüge vollständig implementieren:
  - [ ] Rochade (kurz/lang) — Bedingungen prüfen (`Rook`/`King` unmoved, Felder frei, keine Durchquerung in Schach).
  - [ ] En Passant — Zug-Validierung und Rückgängigmachung (Undo).
  - [ ] Bauernumwandlung (Promotion) — Auswahlmechanismus & regelkonforme Ersetzung.
- [ ] Draw- / Game-End-Checks:
  - [ ] Schachmatt- und Patt-Erkennung.
  - [ ] Unzureichendes Material, 50-Move-Rule, Drei-Zeugen-Regel (threefold repetition).
- [ ] Korrekte Board-Zustandsverwaltung:
  - [ ] Move-History, `undo()` / `redo()`.
  - [ ] Reversible / irreversible Zustandsfelder (z.B. en-passant, Castling-Rechte).

Engine / Suche (optional)
- [ ] Time-Management / Time Controls (Clocks).

UI & UX
- [ ] Eingabemethoden:
  - [ ] Click-to-move, Drag-and-drop, Keyboard-Shortcuts.
  - [ ] Visual Feedback: markiere mögliche Züge, letzte Zug, Check-Hervorhebung.
- [ ] Debug-Overlay: Board-Dumps, Züge-Log, Performance-Counters.
- [ ] Responsive Fenster/Resizing (Viewport / Aspect Ratio für OpenGL).

Priorisierungsvorschlag (kurz)
1. Vollständige `getMoves` + Simulation (`wouldBeInCheckAfterMove`) + Unit-Tests (Perft).
2. Sonderzüge (Rochade, En Passant, Promotion).
3. `isInCheck` & Game-End-Checks (Checkmate/Patt).
4. Undo/Redo.
5. Basis-Engine (Alpha-Beta) + Performance-Optimierungen.
6. UI

## Kurzer Entwicklungsplan
1. `getMoves` für jede Figur korrekt implementieren (inkl. Sonderzüge).
2. Simulationsroutine hinzufügen, um `wouldBeInCheckAfterMove` zu ermitteln.
3. `isInCheck` stabilisieren und in Move-Filter integrieren.

## Build / Run
- Projekt in Visual Studio 2026 öffnen (`.sln` / `.vcxproj`).
- Abhängigkeiten: OpenGL (GLEW/GLFW oder eigenes Setup) — siehe `Dependecies`-Ordner.
- Build-Konfiguration: __Debug__ / __x64__ empfohlen.

--------------- 

Ja das ist mit KI geschrieben weil ich kein bock habe eine Readme zu schreiben heul doch
