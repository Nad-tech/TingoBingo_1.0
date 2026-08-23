# 🤖 TingoBingo

> **A modular C++ robot built with Raylib.**

TingoBingo is an interactive cardboard robot designed to explore animation, game architecture, robot behaviour and AI features through a clean, object-oriented C++ codebase.

---

# 📷 Current Status

🟢 **Active Development**

TingoBingo currently features:

- Independent facial animation systems
- Idle behaviour
- Animation playback and priority systems
- Emotion state management
- Asynchronous speech generation using Piper TTS
- Mouse-controlled pupil tracking
- Automatic searching behaviour
- Ray-based object detection

Tingo is beginning to move beyond simple animation and into **perception and behaviour**.

---

# 🛠 Built With

| Technology | Purpose |
|------------|---------|
| C++20 | Core application |
| Raylib | Rendering, input, collision and audio |
| Piper TTS | Offline text-to-speech generation |
| MSYS2 / MinGW64 | Build environment |
| Visual Studio Code | Development |

---

# 🤖 Current Features

## Robot

- Modular robot architecture
- Object-oriented design
- Layered head components
- Sprite-based rendering
- Centralised behaviour management through `RobotBrain`
- Independent facial components
- Head positioning and rotation
- Automatic return-to-centre behaviour

---

# 🎞️ Animation

- Independent animation system
- Sprite sheet support
- Animation playback control
- Animation state tracking
- Animation priority system
- Higher-priority animations can interrupt lower-priority animations
- Idle animation priority
- Emotion animation priority
- Random idle animations
- Eye blinking
- Ear movement
- Eyebrow movement
- Nose movement
- Mouth idle animation
- Speaking mouth animation
- Head bobbing
- Head wiggle animation
- Antenna movement

### Animation Priority

Animations are assigned a priority level to prevent different controllers from fighting over the same facial feature.

```text
Idle
  ↓
Emotion
```

An emotion animation can interrupt an idle animation, while an idle animation cannot interrupt an active emotion animation.

---

# 😊 Emotion System

- `Emotion` state system
- `EmotionController`
- Current emotion tracking
- Emotion-driven facial animation
- Emotion animation priority
- Separation between emotion logic and facial rendering

Current emotion states include:

```cpp
Neutral
Happy
Sad
Angry
Surprised
```

The emotion system provides a foundation for future emotional states and behaviour.

---

# 🧠 RobotBrain

`RobotBrain` acts as the central behaviour coordinator for TingoBingo.

It currently manages:

- Robot state
- Idle behaviour
- Searching behaviour
- Emotion state
- Speech
- Object detection
- Reactions to detected objects

The Brain separates **robot behaviour and decision-making** from the `Robot` and `Head` classes.

```text
Robot
│
├── Head
│
└── RobotBrain
     ├── SpeechController
     ├── Emotion
     ├── Idle Behaviour
     └── Search Behaviour
          │
          └── Object Detection
```

---

# 👀 Interaction

- Mouse tracking pupils
- Keyboard controlled head rotation
- Automatic head return to centre
- Independent facial components
- Layered facial rendering
- Draggable toys
- Toy interaction
- Object detection through a search ray

---

# 🔎 Search & Object Detection

Tingo now has the beginnings of a simple **robot vision system**.

When Tingo enters the `Searching` state, the `RobotBrain` continuously rotates a search direction.

```text
             search direction
                    ↗
                   /
                  /
                 ●
               Tingo
```

A ray is projected from Tingo's head:

```text
Tingo ●────────────────────────►
             300 pixels
```

The ray is checked against the collision rectangles of registered `Toy` objects.

```text
                 ┌───────────┐
                 │   BALL    │
                 │           │
Tingo ●─────────►│           │
                 └───────────┘
                       ↑
                     HIT
```

The current detection system:

- Maintains a list of `Toy*` search targets
- Generates a rotating search direction
- Creates a 300-pixel search ray
- Checks the ray against toy collision rectangles
- Identifies the object that was detected
- Allows `RobotBrain` to react to the detected object

Current reactions include:

### 🍌 Banana

```text
HEY! A banana!
```

### ⚽ Ball

```text
OH! A ball!
```

This is an early foundation for a future perception system.

The current search pattern is deliberately simple and uses a circular sweep. More natural search behaviour is planned for later.

---

# 🗣️ Speech

- Offline speech generation using Piper
- Background thread speech generation
- Non-blocking speech system
- Automatic speech playback
- Speech state management
- RobotBrain state management
- Automatic return to idle after speaking
- Object-specific speech reactions

Tingo can generate speech without blocking the main animation loop.

---

# 🎯 Behaviour States

Tingo's behaviour is currently managed through a simple state machine.

```text
        ┌──────────┐
        │   Idle   │
        └────┬─────┘
             │
             │ timer
             ▼
      ┌──────────────┐
      │  Searching   │
      └──────┬───────┘
             │
             │ object detected
             ▼
       ┌───────────┐
       │ Reaction  │
       └───────────┘
```

Current `RobotBrain` states include:

```cpp
Idle
Speaking
Searching
```

The state system is intended to expand as Tingo's behaviour becomes more sophisticated.

---

# 🏗️ Project Architecture

```text
Game
│
├── Robot
│   │
│   ├── Head
│   │   ├── Headbase
│   │   ├── Eyes
│   │   ├── Pupils
│   │   ├── Eyebrows
│   │   ├── Mouth
│   │   ├── Nose
│   │   ├── Ears
│   │   └── Antenna
│   │
│   └── RobotBrain
│       │
│       ├── SpeechController
│       │
│       ├── Emotion
│       │
│       └── Search
│           │
│           └── Toy Detection
│
├── Toy
│   ├── Ball
│   └── Banana
│
└── Animation System
```

---

# 🧩 Object Detection Architecture

`Game` owns the actual toy objects.

```text
Game
│
├── Toy ball
├── Toy banana
│
└── vector<Toy*>
          │
          ▼
     RobotBrain
          │
          ▼
      Search Ray
```

The `RobotBrain` does not own the toys.

Instead, it receives pointers to the objects that can currently be detected.

Each `Toy` owns its own collision rectangle:

```cpp
Rectangle collisionBox;
```

This keeps the collision information associated with the object it belongs to.

---

# 🎯 Project Goals

The project focuses on learning and experimenting with:

- Modern C++
- Object-oriented programming
- Game architecture
- Animation systems
- State machines
- Animation priorities
- Threading
- Artificial intelligence
- Robot behaviour
- Perception systems
- Object detection
- Modular software design

The project is intentionally being developed incrementally, with each system providing a foundation for the next.

---

# 🚧 Planned Features

## 🤖 Character & Emotion

- Additional facial expressions
- More complex emotion behaviours
- Emotion transitions
- Emotion-driven speech and reactions
- More expressive body/head movement

## 👀 Perception & Behaviour

- More natural search behaviour
- More advanced object detection
- Object interaction
- Context-aware reactions
- Memory system
- More advanced robot states
- Behaviour trees
- More sophisticated AI behaviour

## 🗣️ Speech & Conversation

- Talking mouth animation improvements
- Speech queue
- Conversation system
- Voice recognition
- Speech-to-text

## 🎮 Fun Features

- Mini games
- Music and dancing
- Guitar interaction
- Customisation
- Learning activities

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
