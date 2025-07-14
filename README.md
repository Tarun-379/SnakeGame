# SnakeGame
first app i build using cpp also the project displaying my control over raylib library


# 🐍 Snake Game (C++ & Raylib)

A modern and customizable version of the classic Snake game, built using **C++** and **[raylib](https://www.raylib.com/)**. This project includes sound effects, a scoring system, high score tracking, and a polished macOS `.app` bundle with a custom icon!

---

## 🎮 Features

- ✅ **Classic Snake Gameplay**: Eat food to grow, avoid crashing into yourself.
- 🎯 **Self-Collision Detection**: Game ends when the snake hits itself.
- ⏸️ **Pause Functionality**: Press `P` to pause/resume the game.
- 🔁 **Restart Option**: Press `R` after game over to restart without relaunching.
- 🔊 **Sound Effects**:
  - `eat.wav` — when food is eaten.
  - `over.wav` — on game over.
- 🏆 **High Score System**:
  - Top 5 high scores are saved to `highscore.txt`.
  - Includes player names.
  - Shows "New High Score!" message when applicable.
- 👤 **Name Entry**: Prompt to enter your name when you achieve a high score.
- 💾 **Persistent Score Storage**: Saved in a plain-text file for easy portability.
- 💻 **macOS App Bundle**:
  - Packaged as a `.app` with an icon.
  - Double-click to launch like any other Mac application.

---

## 🧠 Controls

| Key        | Action            |
|------------|-------------------|
| Arrow Keys | Move Snake        |
| `Space`    | Pause/Resume      |
| `R`        | Restart Game      |
| `Esc`      | Exit Game         |

---

## 🛠️ Build Instructions

### Prerequisites
- macOS with Xcode command line tools installed
- [raylib installed](https://github.com/raysan5/raylib/wiki/Working-on-macOS)
- C++ compiler (e.g., `g++` or `clang++`)

### Build Command

```bash
g++ -o snake SnakeGame.cpp -lraylib -std=c++17 -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL





SnakeGame/
│
├── SnakeGame.cpp           # Main source code
├── snake.png               # Icon source image
├── snake.icns              # Final app icon
├── eat.wav                 # Eat sound
├── over.wav                # Game over sound
├── highscore.txt           # Stored high scores
├── SnakeGame.app/          # macOS application bundle
│   ├── Contents/
│       ├── MacOS/SnakeGame
│       └── Resources/snake.icns
└── README.md
