# Phase 9 Card Game (C Project)

## Overview
This project is a C implementation of **Phase 9**, a card game inspired by Phase 10.  
It was developed for a programming assignment to practice structs, dynamic memory, file I/O, and game logic.

## Features
- Two-player gameplay
- Deck initialization and shuffling
- Phases 1–9 with sets and runs
- Skip and wild cards
- Leaderboard support (`leaderboard.txt` file required)

## How to Compile
Run:
```bash
gcc phase9.c -o phase9
```

Or with a Makefile:
```bash
make
```

## How to Run
```bash
./phase9
```

## File Descriptions
- **phase9.c** – main game logic
- **phase9.h** – macros, struct definition, and prototypes
- **leaderboard.txt** – leaderboard file (not included in repo; create manually)

## Future Improvements
- Full multiplayer expansion
- Better input validation
- Save/load game states
