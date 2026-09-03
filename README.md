# 🤖 TingoBingo

**An interactive cardboard robot built with C++20 and Raylib.**

TingoBingo is an ongoing project to build a virtual interactive robot with its own behaviour, emotions, facial animation, speech, object interaction and eventually more autonomous decision-making.

The project is deliberately modular. The robot's behaviour, head, facial features, animation, speech and objects are separate systems that communicate with each other.


## Current Status

🚧 **Active development**

The core robot, animation system, speech system, object interaction and autonomous searching behaviour are currently being developed and expanded.


# ✨ Current Features

## 🤖 Robot

* Cardboard-style robot character.
* Modular robot architecture.
* Independent head and facial components.
* Head rotation using sprite-sheet frames.
* Automatic return to the forward-facing position.
* Pupil tracking.
* Looking at specific world positions.
* Speaking state.
* Emotional states.


## 🧠 RobotBrain

`RobotBrain` is Tingo's high-level behaviour coordinator.

It decides what Tingo should be doing and communicates with the other systems responsible for actually performing those actions.

### Current Behaviour States

```text
                 ┌───────────┐
                 │   IDLE    │
                 └─────┬─────┘
                       │
                   10 seconds
                       │
                       ▼
               ┌───────────────┐
               │   SEARCHING   │
               └───────┬───────┘
                       │
                 object detected
                       │
                       ▼
               ┌───────────────┐
               │   REACTING    │
               └───────┬───────┘
                       │
                reaction complete
                       │
                       ▼
                 ┌───────────┐
                 │   IDLE    │
                 └───────────┘
```

Current states:

* `Idle`
* `Searching`
* `Reacting`

RobotBrain also manages:

* Emotions.
* Speech requests.
* Object interactions.
* Object detection.
* Search behaviour.
* Reaction cooldowns.
* Behaviour timers.


# 👁️ Searching & Object Detection

Tingo can autonomously search his environment for registered objects.

After remaining idle for 10 seconds, Tingo enters `Searching`.

During searching:

1. The search angle continuously changes.
2. The angle is converted into a 2D direction vector.
3. A 300-pixel search ray is projected from Tingo's head.
4. Tingo's pupils look along the same direction as the ray.
5. The ray is tested against registered object collision rectangles.
6. The first object intersected by the ray becomes the detected object.
7. Tingo stops searching and enters `Reacting`.

```text
             Search Angle
                  │
                  ▼
            Direction Vector
                  │
          ┌───────┴────────┐
          ▼                ▼
       Eye Gaze         Search Ray
                             │
                             ▼
                    Collision Testing
                             │
                       Object Found
                             │
                             ▼
                         Reacting
```

The visual gaze and collision ray use the **same direction**, keeping what Tingo is looking at synchronised with what he is actually detecting.

### Current Detectable Objects

* 🟡 Ball
* 🍌 Banana

When an object is detected, Tingo can:

* Look directly at it.
* Change emotion.
* Remain focused on it.
* Deliver an object-specific speech reaction.

The collision system tests the search ray against the object's complete rectangular boundary:

```text
       Top
   ┌───────────┐
   │           │
Left│  Object   │Right
   │           │
   └───────────┘
      Bottom
```

The system also handles the case where the ray begins inside the collision rectangle.


# 🖱️ Object Interaction

Objects can be picked up and moved using the mouse.

The interaction system distinguishes between two types of object references:

```text
targetObject
    │
    └── Object currently being held/interacted with


detectedObject
    │
    └── Object found by the autonomous search system
```

When an object is held:

* Tingo looks at it.
* Tingo enters `Reacting`.
* Object-specific reactions can occur.
* Speech can be triggered.
* A reaction cooldown prevents repeated responses.


# 🗣️ Speech

Speech is handled by `SpeechController` rather than directly by the robot.

### Speech Pipeline

```text
             Speech Request
                    │
                    ▼
              RobotBrain
                    │
                    ▼
           SpeechController
                    │
                    ▼
              Generating
                    │
              Piper / FFmpeg
                    │
                    ▼
                WAV Ready
                    │
                    ▼
                Playing
                    │
                 Raylib
                    │
                    ▼
                  Idle
```

Speech generation runs on a worker thread so that Piper/FFmpeg processing does not block the main game loop.

Raylib audio operations are handled on the main thread.

The speech controller currently distinguishes between:

* `Idle`
* `Generating`
* `Playing`

This separation prevents speech generation from being confused with actual audio playback.


# ❤️ Emotions

Current emotional states:

* `Neutral`
* `Happy`
* `Sad`
* `Angry`
* `Surprised`

Currently implemented behaviour primarily uses:

* Neutral
* Happy

Emotions can affect Tingo's facial animation and behaviour.


# 🎭 Facial Animation

Tingo's head is constructed from independently controlled components.

```text
                    HEAD
                      │
        ┌─────────────┼─────────────┐
        │             │             │
     HeadBase       Face        Movement
        │             │             │
        │       ┌─────┼─────┐       │
        │       │     │     │       │
        │     Eyes  Mouth  Brows    │
        │       │           │       │
        │     Pupils        │       │
        │                   │       │
        └──── Ears / Nose / Antenna┘
```

Current components:

* Head base.
* Eyes.
* Pupils.
* Eyebrows.
* Mouth.
* Nose.
* Ears.
* Antenna.

When the head is facing forward, the facial components are rendered independently.

When the head is rotated, the head-base artwork is rendered on its own because the facial features are already included in the rotated head artwork.


# 🎞️ Animation System

The project contains a reusable `Animation` class for sprite-sheet animation.

It supports:

* Sprite-sheet frame animation.
* Configurable frame duration.
* Animation ranges.
* Play/stop control.
* Direct frame control.
* Previous/next frame movement.
* Animation priorities.
* Idle animations.
* Emotion animations.

Current priorities:

```text
Emotion
   ▲
   │
   │ higher priority
   │
Idle
```

This allows an emotional animation to take control over a lower-priority idle animation.


# 😴 Idle Behaviour

Tingo has several independent idle behaviours designed to make the robot feel less mechanical.

Current idle animations include:

* 👀 Eye blinking.
* 👂 Ear movement.
* 📡 Antenna movement.
* 🤨 Eyebrow movement.
* 👃 Nose movement.
* 🤖 Head bobbing.
* ↔️ Head wiggling.

Many of these behaviours use randomised timing so that they do not repeat at exactly the same intervals.


# 🏗️ Architecture

The current high-level structure is:

```text
Game
 │
 ├── Robot
 │    │
 │    ├── RobotBrain
 │    │    │
 │    │    ├── Behaviour
 │    │    ├── Emotions
 │    │    ├── Searching
 │    │    ├── Object Detection
 │    │    └── SpeechController
 │    │
 │    └── Head
 │         │
 │         ├── HeadBase
 │         ├── Eyes
 │         ├── Pupils
 │         ├── Eyebrows
 │         ├── Mouth
 │         ├── Nose
 │         ├── Ears
 │         └── Antenna
 │
 └── Objects
      │
      ├── Ball
      └── Banana
```

### Game

Controls the main application loop:

```text
Initialise
    ↓
HandleInput
    ↓
Update
    ↓
Draw
    ↓
Repeat
    ↓
Shutdown
```

### Robot

Acts as the interface between `Game`, `RobotBrain` and `Head`.

### RobotBrain

Controls high-level behaviour and decisions.

### Head

Coordinates the robot's visual head and facial components.

### Sprite

Provides common functionality for drawable and animated sprites.

### Object

Represents interactive objects that can be manipulated and detected.

### SpeechController

Manages speech generation and audio playback.


# 📁 Project Structure

```text
TingoBingo/
│
├── assets/
│   └── images/
│
├── include/
│   ├── Animation.h
│   ├── Constants.h
│   ├── Emotion.h
│   ├── Game.h
│   ├── Input.h
│   ├── Object.h
│   ├── Robot.h
│   ├── RobotBrain.h
│   ├── Speech.h
│   ├── SpeechController.h
│   ├── Sprite.h
│   └── head/
│
├── src/
│   ├── Animation.cpp
│   ├── Game.cpp
│   ├── Robot.cpp
│   ├── RobotBrain.cpp
│   ├── Speech.cpp
│   ├── SpeechController.cpp
│   ├── Sprite.cpp
│   └── head/
│
├── utilities/
│
└── build/
```


# 🛠️ Technologies

* **C++20**
* **Raylib**
* **Piper**
* **FFmpeg**
* **MSYS2 / MinGW**
* **Visual Studio Code**
* **Git**


# 🔮 Future Ideas

These are planned ideas, not currently implemented features.

## Behaviour

* Expand RobotBrain behaviour states.
* More autonomous behaviour.
* Behaviour priorities.
* More complex behaviour sequences.
* More object-specific reactions.
* Better separation between temporary reactions and long-running behaviour.

## 👁️ Vision

* More detectable objects.
* More sophisticated object detection.
* Object recognition.
* Improved search behaviour.
* Interaction with objects beyond pickup and detection.

## 🗣️ Voice

* More speech reactions.
* Speech driven by behaviour.
* Speech recognition.
* Voice commands.
* Two-way voice interaction.
* Improved speech cancellation and lifecycle handling.

## ❤️ Emotions

* Fully implement Sad, Angry and Surprised.
* Emotion transitions.
* More expressive facial animations.
* Emotion-driven behaviour.
* Combining emotion, speech and interaction.

## 🎭 Animation

* More facial expressions.
* More eye animations.
* More mouth animations.
* More eyebrow expressions.
* More coordinated animations.
* Improved animation blending and priorities.

## 🧠 Personality

The longer-term goal is for Tingo's personality to emerge from his behaviour rather than simply playing predefined responses.

Possible systems:

* Memory of previous interactions.
* Context-dependent reactions.
* Repeated-interaction responses.
* More unpredictable behaviour.
* Personality traits affecting decisions.

## 🎮 Activities

Possible future interactive features:

* Mini-games.
* Learning activities.
* Music interaction.
* Dancing.
* Guitar interaction.
* More interactive toys.

## 🤖 AI / Behaviour Systems

Longer-term possibilities include:

* Memory systems.
* Behaviour trees.
* Context-aware decision making.
* More autonomous decision making.
* Object recognition.
* AI-assisted conversation.


# 🎯 Long-Term Goal

The long-term goal of TingoBingo is to turn a simple Raylib robot into an interactive character with:

```text
          ┌──────────────────┐
          │     TingoBingo   │
          └────────┬─────────┘
                   │
       ┌───────────┼───────────┐
       │           │           │
   Behaviour    Perception   Interaction
       │           │           │
       ├───────┬───┴───────┬───┤
       │       │           │   │
    Emotion  Vision      Speech Memory
       │       │           │   │
       └───────┴───────────┴───┘
                   │
                   ▼
              Personality
```

The project will continue to be developed incrementally, with each major system kept modular and understandable before adding more complexity.
