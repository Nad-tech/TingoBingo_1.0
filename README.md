# 🤖 TingoBingo

> **A modular C++ robot built with Raylib.**
>
> TingoBingo is an interactive cardboard robot designed to explore animation, game architecture and AI features through a clean, object-oriented codebase.

---

## 📷 Current Status

🟢 Active Development

---

## 🛠 Built With

| Technology | Purpose |
|------------|---------|
| C++20 | Core application |
| Raylib | Rendering, input and audio |
| Piper TTS | Offline text-to-speech generation |
| MSYS2 / MinGW64 | Build environment |
| Visual Studio Code | Development |

---

# Current Features

### Robot

- Modular robot architecture
- Layered head components
- Sprite-based rendering
- Object-oriented design

### Animation

- Independent animation system
- Sprite sheet support
- Random idle animations
- Eye blinking
- Ear movement
- Eyebrow movement
- Nose movement
- Mouth idle animation
- Head bobbing
- Head wiggle animation

### Interaction

- Mouse tracking pupils
- Keyboard controlled head rotation
- Automatic return to centre

### Speech

- Offline speech generation using Piper
- Background thread speech generation
- Non-blocking speech system
- Automatic speech playback
- RobotBrain state management
- Automatic return to idle after speaking

---

# Project Architecture

```
Game
│
├── Robot
│   ├── Head
│   ├── IdleController
│   └── RobotBrain
│        └── SpeechController
│              ├── Piper
│              └── Raylib Audio
│
└── Animation System
```

---

# Project Goals

The project focuses on learning and experimenting with:

- C++
- Object-oriented programming
- Game architecture
- Animation systems
- State machines
- Threading
- Artificial intelligence
- Robot behaviour

---

# Planned Features

- Facial expressions
- Talking mouth animation
- Speech queue
- Conversation system
- Emotion system
- Object interaction
- Memory system
- Voice recognition
- Behaviour trees
- Mini games
- Music and dancing
- Customisation

---

# Current Project Structure

```
include/
src/
assets/
tools/
scripts/
build/
```

---

# Author

**Dan3rdeye**

Learning modern C++ by building an interactive robot from the ground up.