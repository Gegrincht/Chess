# Copilot Instructions

## General Guidelines
- Use OpenGL for windowing/rendering.

## Game Logic
- Check move legality inside `getMoves` by simulating each move and using `continue` to skip moves that leave the king in check.