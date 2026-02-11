# MakingChess

Kleines Schachprojekt in C++ (Visual Studio 2026). Ziel ist eine saubere Spiel-Engine mit OpenGL-basiertem Rendering und vollständiger Zugvalidierung.

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

Viele Prüfungen zur Zuglegitimität fehlen noch oder sind unvollständig.

Viele Prüfungen zur Zuglegitimität fehlen noch oder sind unvollständig.

Viele Prüfungen zur Zuglegitimität fehlen noch oder sind unvollständig.

## TODO-Liste (Kurz)
- [ ] `std::cout << format(Piece.type, "name")` und Ausgabe als "char" möglich machen  
  - Ziel: bequemes Ausgeben von Figurenname oder Symbol (z.B. `K` / "King").
- [ ] Movement-Legality-Checks implementieren  
  - Prüfen, ob eine Figur diesen Bewegungstyp rechtmäßig ausführen darf (z.B. Springer, Läufer-Diagonalen, Pfad-Freie Felder).
- [ ] Prüfen, ob ein geplanter Zug den eigenen König in Schach setzt  
  - Vermeidung von Zügen, die zum illegalen Zustand führen.
- [ ] Implementiere folgende Methoden:
  - `std::vector<Move> getMoves(char file, int rank);`
  - `std::vector<Move> getMoves(const Piece& curPiece);`
  - `bool isInCheck(Color color);`
  - `bool wouldBeInCheckAfterMove(const Move& move);`

Hinweis: Bei `getMoves` sollen Züge durch Simulieren angewendet und solche, die den König in Schach lassen, mit `continue` übersprungen werden (siehe Projektvorgabe in `.github/copilot-instructions.md`).

## Erweiterte TODO-Liste (fehlende / empfohlene Punkte)
Diese Liste ergänzt die Kernaufgaben um oft übersehene, aber wichtige Teile des Projekts.

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

Notation / Import & Export
- [ ] FEN-Parsing & -Generierung (`loadFEN`, `saveFEN`) — für Tests und Position-Setup.
- [ ] PGN-Export / Grundlegende PGN-Parsing-Unterstützung.

Tests & Verifikation
- [ ] Perft-Tests für Move-Generator (Knoten-Zählung).
- [ ] Unit-Tests für:
  - [ ] `getMoves` für jede Figur.
  - [ ] `isInCheck` / `wouldBeInCheckAfterMove`.
- [ ] CI-Integration (z. B. GitHub Actions) für Build + Tests.

Engine / Suche (optional)
	- [ ] Einfache Bewertungsfunktion (Material + Position).
- [ ] Minimax / Alpha-Beta mit Iterative Deepening.
- [ ] Transposition Table (Zobrist-Hashing) für Performance.
- [ ] Time-Management / Time Controls (Clocks).

UI & UX
- [ ] Eingabemethoden:
  - [ ] Click-to-move, Drag-and-drop, Keyboard-Shortcuts.
  - [ ] Visual Feedback: markiere mögliche Züge, letzte Zug, Check-Hervorhebung.
- [ ] Debug-Overlay: Board-Dumps, Züge-Log, Performance-Counters.
- [ ] Responsive Fenster/Resizing (Viewport / Aspect Ratio für OpenGL).

Performance & Architektur
- [ ] Überlege Bitboards für Performance (später) vs. Array-Board für Einfachheit.
- [ ] Profiler-Integration / Hotspot-Analyse (Move-Generator, Make/Unmake Move).
- [ ] Memory-Safety & RAII-Pattern befolgen (keine globalen Roh-Pointer).

Build / DevOps / Dokumentation
- [ ] GitHub Actions: Build + Unit-Tests + simple perft-Checks.
- [ ] Code-Style / Linter konfigurieren.
- [ ] Entwickler-Dokumentation:
  - [ ] `CONTRIBUTING.md`, kurze Architektur-Übersicht, HowTo-Test.
- [ ] Logging / Verbose-Level (Debug/Info/Error).

Priorisierungsvorschlag (kurz)
1. Vollständige `getMoves` + Simulation (`wouldBeInCheckAfterMove`) + Unit-Tests (Perft).
2. Sonderzüge (Rochade, En Passant, Promotion).
3. `isInCheck` & Game-End-Checks (Checkmate/Patt).
4. FEN/PGN + Undo/Redo.
5. Basis-Engine (Alpha-Beta) + Performance-Optimierungen.
6. UI-Verbesserungen, CI, Dokumentation.

## Kurzer Entwicklungsplan
1. `getMoves` für jede Figur korrekt implementieren (inkl. Sonderzüge).
2. Simulationsroutine hinzufügen, um `wouldBeInCheckAfterMove` zu ermitteln.
3. `isInCheck` stabilisieren und in Move-Filter integrieren.
4. Benutzerfreundliche Ausgabe für `Piece` (operator<< / format).
5. Perft-Tests schreiben und in CI aufnehmen.

## Build / Run
- Projekt in Visual Studio 2026 öffnen (`.sln` / `.vcxproj`).
- Abhängigkeiten: OpenGL (GLEW/GLFW oder eigenes Setup) — siehe `Dependecies`-Ordner.
- Build-Konfiguration: __Debug__ / __x64__ empfohlen.

Wenn du möchtest, kann ich die README noch in ein ausführlicheres Entwickler-Guide-Format umwandeln oder direkt mit der Implementierung einer genannten Methode in `Chess/src` anfangen (z. B. `getMoves` / `isInCheck` / FEN-Loader).