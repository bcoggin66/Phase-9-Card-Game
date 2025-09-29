# 🎴 Phase 9 Card Game (C Project)

![C](https://img.shields.io/badge/language-C-blue.svg)
![Status](https://img.shields.io/badge/status-completed-brightgreen.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

---

## 📌 Overview
This project is a C implementation of **Phase 9**, a card game inspired by *Phase 10*.  
It was developed as part of a programming course assignment to practice:

- Structs and arrays  
- Dynamic memory handling  
- File I/O for saving leaderboard data  
- Sorting algorithms (using `qsort`)  
- Game loop design and logic  

The game supports multiple players, tracks progress through phases, and maintains a leaderboard between sessions.

---

## ✨ Features
- 🎮 **Multiplayer Gameplay** – specify number of players at runtime  
- 🃏 **Deck Handling** – initialize, shuffle, draw, and discard cards  
- 🔄 **Phase Progression** – phases 1–9 with sets and runs checking  
- 🚫 **Special Cards** – skip cards (lose turn) and wild cards (flexible use)  
- 🏆 **Leaderboard System** – saves wins to `leaderboard.txt`  
- 🔒 **Input Validation** – prevents invalid menu and card selection  

---

## 🛠️ Compilation Instructions

You can compile this project in **two different ways**:


With GCC:
```bash
gcc phase9.c -o phase9```

Using the Makefile (recommended)
If you have `make` installed, simply run:
```bash
make```

