# 🤖 TingoBingo

> **A modular C++ robot built with Raylib.**
>
> TingoBingo is an interactive cardboard robot designed to explore animation, game architecture and AI features through a clean, object-oriented codebase.

---

## 📷 Current Status

🟢 **Active Development**

TingoBingo currently features independent facial animation systems, idle behaviour, an animation priority system, an emotion state system, and asynchronous speech generation.

---

## 🛠 Built With

| Technology         | Purpose                           |
| ------------------ | --------------------------------- |
| C++20              | Core application                  |
| Raylib             | Rendering, input and audio        |
| Piper TTS          | Offline text-to-speech generation |
| MSYS2 / MinGW64    | Build environment                 |
| Visual Studio Code | Development                       |

---

# Current Features

## 🤖 Robot

* Modular robot architecture
* Object-oriented design
* Layered head components
* Sprite-based rendering
* Centralised behaviour management through `RobotBrain`

## 🎞️ Animation

* Independent animation system
* Sprite sheet support
* Animation playback control
* Animation state tracking
* Animation priority system
* Higher-priority animations can interrupt lower-priority animations
* Idle animation priority
* Emotion animation priority
* Random idle animations
* Eye blinking
* Ear movement
* Eyebrow movement
* Nose movement
* Mouth idle animation
* Head bobbing
* Head wiggle animation

### Animation Priority

Animations are assigned a priority level to prevent different controllers from fighting over the same facial feature.

```text
Idle
  ↓
Emotion
```

An emotion animation can interrupt an idle animation, while an idle animation cannot interrupt an active emotion animation.

---

## 😊 Emotion System

* `Emotion` state system
* `EmotionController`
* Current emotion tracking
* Emotion-driven facial animation
* Emotion animation priority
* Separation between emotion logic and facial rendering

The emotion system is designed to provide a foundation for future emotional states and behaviours.

---

## 🧠 RobotBrain

`RobotBrain` acts as the central behaviour coordinator for TingoBingo.

It currently manages:

* Robot state
* `IdleController`
* `EmotionController`
* `SpeechController`

This separates **robot behaviour and decision-making** from the `Robot` and `Head` classes.

```text
Robot
│
├── Head
│
└── RobotBrain
     ├── IdleController
     ├── EmotionController
     └── SpeechController
```

---

## 👀 Interaction

* Mouse tracking pupils
* Keyboard controlled head rotation
* Automatic head return to centre
* Independent facial components
* Layered facial rendering

---

## 🗣️ Speech

* Offline speech generation using Piper
* Background thread speech generation
* Non-blocking speech system
* Automatic speech playback
* Speech state management
* RobotBrain state management
* Automatic return to idle after speaking

---

# Project Architecture

```text
Game
│
├── Robot
│   │
│   ├── Head
│   │    ├── Headbase
│   │    ├── Eyes
│   │    ├── Pupils
│   │    ├── Eyebrows
│   │    ├── Mouth
│   │    ├── Nose
│   │    ├── Ears
│   │    └── Antenna
│   │
│   └── RobotBrain
│        │
│        ├── IdleController
│        ├── EmotionController
│        └── SpeechController
│              │
│              ├── Piper
│              └── Raylib Audio
│
└── Animation System
```

---

# 🎯 Project Goals

The project focuses on learning and experimenting with:

* Modern C++
* Object-oriented programming
* Game architecture
* Animation systems
* State machines
* Animation priorities
* Threading
* Artificial intelligence
* Robot behaviour
* Modular software design

---

# 🚧 Planned Features

### 🤖 Character & Emotion

* Additional facial expressions
* Sad, angry and surprised emotions
* More complex emotion behaviours
* Emotion transitions
* Emotion-driven speech and reactions

### 🗣️ Speech & Conversation

* Talking mouth animation improvements
* Speech queue
* Conversation system
* Voice recognition
* Speech-to-text

### 🧠 Behaviour & AI

* Object interaction
* Memory system
* Behaviour trees
* More advanced robot states
* Context-aware behaviour

### 🎮 Fun Features

* Mini games
* Music and dancing
* Guitar interaction
* Customisation
* Learning activities

---

# 📁 Current Project Structure

```text
include/
src/
assets/
tools/
scripts/
build/
```

---

# 👨‍💻 Author

**Dan3rdeye**

Learning modern C++ by building an interactive robot from the ground up.
