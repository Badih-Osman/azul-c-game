
# 🎯 AZUL – C Implementation of the Tile-Laying Board Game

Welcome to the **Azul game implementation in C**, a console-based version of the famous tile-laying board game **Azul**. This project aims to replicate the core mechanics of the game while practicing structured programming, memory management, and data modeling in C.

---

## 📜 Table of Contents
- [About the Game](#about-the-game)
- [Project Structure](#project-structure)
- [Features](#features)
- [Gameplay Overview](#gameplay-overview)
- [Data Modeling](#data-modeling)
- [Compilation & Execution](#compilation--execution)
- [Screenshots / Demo](#screenshots--demo)
- [Known Limitations](#known-limitations)
- [Possible Improvements](#possible-improvements)
- [Authors](#authors)
- [License](#license)

---

## 🎮 About the Game

Azul is a strategy board game in which players take turns drafting colored tiles from factories to their player board. The goal is to complete rows on your wall in a way that scores the most points while minimizing penalties.

This C version of Azul recreates the mechanics of:
- Tile drafting from factories and central reserve.
- Tile placement on motif lines.
- Scoring mechanism.
- Penalty system.
- Wall construction and endgame conditions.

---

## 📁 Project Structure

```
Azul/
├── src/
│   ├── main.c
│   ├── joueur.c / joueur.h
│   ├── plateau.c / plateau.h
│   ├── fabrique.c / fabrique.h
│   ├── utils.c / utils.h
├── include/
│   └── All header files
├── assets/
│   └── Game illustrations or ASCII visuals (optional)
├── README.md
└── Makefile
```

---

## ✨ Features

✔ Turn-based gameplay for multiple players  
✔ Modular structure using header and source files  
✔ Scoring system including motif lines, completed rows, and penalties  
✔ Factory and reserve management system  
✔ Structured data types for players, walls, penalties, etc.  
✔ Easy-to-read console output  

---

## 📖 Gameplay Overview

1. **Start of Round**: Factories are filled with tiles from the reserve.
2. **Player Turn**:
   - Choose a factory or the central reserve.
   - Pick all tiles of a chosen color.
   - Remaining tiles (if any) go to the central reserve.
   - Place chosen tiles on motif lines or floor line (if necessary).
3. **End of Round**:
   - Tiles from completed motif lines are moved to the wall.
   - Points are awarded; penalties applied.
   - Refill factories from the bag.
4. **End of Game**: Triggered when a row on the wall is fully completed by a player.

---

## 🧠 Data Modeling

The game uses structured data types to represent all core components:

### `S_joueur`
```c
typedef struct {
    char *pseudo;
    int score;
    int motif[5];
    int mur[5][5];
    int ligne_plancher[7];
    int nb_tuiles_plancher;
} S_joueur;
```

### `S_fabrique`
```c
typedef struct {
    int tuiles[TAILLE_FABRIQUE];
    int nb_tuiles_restantes;
} S_fabrique;
```

### `S_plateau`, `S_réserve`, `S_pénalité`, etc.
Each struct models a key part of the game such as the board, tile bag, scoring system, etc.  
Integer arrays are used to model tile types and positions efficiently.

---

## ⚙️ Compilation & Execution

### 🔧 Requirements:
- GCC Compiler (Linux / macOS / Windows with MinGW)
- Make (optional, for easier build process)

### 🔨 Compile manually:
```bash
gcc -o azul src/*.c
./azul
```

### 📦 Or use Makefile:
```bash
make
./azul
```

---

## 🖼️ Screenshots / Demo

*Feel free to add screenshots or a short terminal video demo here.*

---

## 🐛 Known Limitations
- No graphical interface (console only)
- No AI players yet
- Minimal input validation

---

## 🚀 Possible Improvements
- Add a basic AI opponent
- Implement a graphical interface using SDL or ncurses
- Improve user interface and input prompts
- Save/Load game functionality
- Multiplayer over network

---

## 👥 Authors
  
- **Badih Osman**  


Project completed as part of an academic software development project (2023/E1).

---

## 📄 License

This project is licensed under the [MIT License](LICENSE), unless specified otherwise.

---

### 💬 Feel free to fork, contribute, or suggest improvements. Happy coding!
