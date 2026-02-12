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

TODO-Liste (Kurz)
- [ ] Implementiere folgende Methoden:
  - [x] `bool isEmpty(int x, int y);`
    - Prüfe ob feld Leer ist.
  - [ ] `bool isEnemy(int x, int y, Color ownColor);`
    - Prüfe ob im Feld ein gegner ist.
  - [ ] `bool outOfBoard(int x, int y)`
    - 2D version vom `outOfBoard(int x);` was schon implimentiert ist.
  - [ ] `std::vector<Move> getMoves(char file, int rank);`
    - Gehe durch jedes Piece und berechne jeden möglichen Zug.
    - Für jeden möglichen Zug wird `isLegal` aufgerufen & wenn true:
      - wird der Zug zur Vektor-Liste hinzugefügt
    - nachdem alle theoretisch möglichen Züge durchgegangen wurden (z. B.: von B2 nach A1, A2, A3 usw. – für jedes Feld auf dem Brett wird isLegal aufgerufen)
  - [ ] `bool inCheck(Color color);`
    - Prüft, ob der König der angegebenen Farbe im Schach steht.
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
