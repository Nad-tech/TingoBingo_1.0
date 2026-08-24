# TingoBingo

TingoBingo is a modular C++20/Raylib virtual cardboard robot.

The project started as a simple animated robot and is gradually becoming
a small interactive character with its own behaviour, emotions, facial
animation, speech, object interaction, and eventually more autonomous
behaviour.

The goal is not to build a generic game framework. The goal is to build
**Tingo** --- a character whose systems work together to make him feel
alive.

------------------------------------------------------------------------

## Current Features

### Robot Architecture

Tingo is split into several cooperating systems:

-   `Robot` --- the main interface for the robot.
-   `RobotBrain` --- controls behaviour and high-level state.
-   `Head` --- coordinates the visual components of the head.
-   `Animation` --- provides reusable sprite-sheet animation.
-   `Emotion` --- defines Tingo's high-level emotional states.
-   `SpeechController` --- manages asynchronous speech generation and
    playback.
-   `Speech` --- handles Piper and FFmpeg speech generation.
-   `Toy` --- provides interactive objects that Tingo can pick up and
    manipulate.

The general relationship is:

``` text
                    Robot
                   /     \
                  /       \
         RobotBrain       Head
             |              |
        Behaviour       Facial features
             |              |
          Speech       Eyes / Mouth /
                       Eyebrows / Pupils /
                       Nose / Ears / Antenna
```

`Robot` acts as the bridge between the behaviour system and the visual
system.

------------------------------------------------------------------------

## Behaviour

`RobotBrain` uses a high-level state system to control what Tingo is
doing.

Current behaviour includes states for:

-   Idle
-   Speaking
-   Happy
-   Sad
-   Angry
-   Surprised
-   Searching
-   Interaction

The intention is for `RobotBrain` to become the central place where
Tingo's behaviour is decided, while the lower-level systems remain
responsible for carrying out that behaviour.

------------------------------------------------------------------------

## Head and Facial Animation

The head is composed of independently controlled visual components:

-   Head base
-   Eyes
-   Mouth
-   Eyebrows
-   Pupils
-   Nose
-   Ears
-   Antenna

This allows Tingo's facial features to animate independently rather than
requiring every facial expression to be baked into a single sprite.

For example:

``` text
Head rotation
      +
Eye animation
      +
Mouth animation
      +
Eyebrow animation
      +
Pupil movement
      =
Tingo's current expression
```

When the head is facing forward, the facial components can be animated
independently.

During head rotation, the rotated head artwork provides the appropriate
head appearance.

------------------------------------------------------------------------

## Animation System

The project uses a reusable `Animation` class for sprite-sheet
animation.

Animations track:

-   Current frame
-   Frame dimensions
-   Frame timing
-   Start and end frames
-   Playback state
-   Animation priority

Two animation priorities currently exist:

``` cpp
AnimationPriority::Idle
AnimationPriority::Emotion
```

This allows more important animations to interrupt lower-priority idle
animations.

For example:

``` text
Idle blink
     ↓
Emotion animation starts
     ↓
Emotion takes priority
     ↓
Emotion finishes
     ↓
Idle behaviour continues
```

------------------------------------------------------------------------

## Emotion System

Tingo currently has the following high-level emotions:

``` cpp
Neutral
Happy
Sad
Angry
Surprised
```

Emotions are represented separately from the individual facial
animations.

`RobotBrain` decides Tingo's emotional state, while the head and facial
components use that state to determine how Tingo looks.

This separation allows behaviour and presentation to evolve
independently.

------------------------------------------------------------------------

## Speech

Tingo can generate and play speech asynchronously.

The speech pipeline is:

``` text
RobotBrain
     ↓
SpeechController
     ↓
Background worker thread
     ↓
Speech
     ↓
Piper
     ↓
speech_raw.wav
     ↓
FFmpeg
     ↓
speech.wav
     ↓
Main game thread
     ↓
Raylib playback
```

### Why speech is asynchronous

Piper and FFmpeg can take noticeable amounts of time to generate audio.

They therefore run on a background thread so that the main Raylib loop
can continue updating and drawing Tingo.

The speech lifecycle is separated into distinct stages:

``` text
Generating
    ↓
WAV Ready
    ↓
Playing
    ↓
Finished
```

`SpeechController` owns the worker thread and coordinates the hand-off
between background speech generation and main-thread audio playback.

The speech worker is joinable and supports shutdown through an atomic
cancellation flag.

------------------------------------------------------------------------

## Interaction

Tingo can interact with objects in the game world.

The current toy system supports:

-   Loading toy sprites
-   Positioning toys
-   Mouse interaction
-   Dragging
-   Collision rectangles
-   Identifying toys by name

The intention is for this system to become the foundation for more
interesting object interaction.

Eventually Tingo should be able to recognise an object, react to it, and
incorporate it into his behaviour rather than simply treating it as a
drawable object.

------------------------------------------------------------------------

## Project Structure

The project is organised roughly as follows:

``` text
TingoBingo/
├── assets/
│   ├── audio/
│   └── images/
│
├── include/
│   ├── head/
│   └── ...
│
├── src/
│   ├── head/
│   ├── Animation.cpp
│   ├── Game.cpp
│   ├── Input.cpp
│   ├── Robot.cpp
│   ├── RobotBrain.cpp
│   ├── Speech.cpp
│   ├── SpeechController.cpp
│   ├── Sprite.cpp
│   ├── Toy.cpp
│   └── main.cpp
│
├── tools/
│   ├── piper/
│   └── ffmpeg/
│
├── build/
│
└── scripts/
```

------------------------------------------------------------------------

## Technology

TingoBingo is currently built with:

-   **C++20**
-   **Raylib**
-   **MinGW / MSYS2**
-   **VS Code**
-   **Piper** for text-to-speech generation
-   **FFmpeg** for speech processing

The project is currently developed on Windows.

------------------------------------------------------------------------

## Design Philosophy

The project is intentionally modular.

Systems should have clear responsibilities rather than one enormous
`Robot` class containing everything.

For example:

``` text
Robot
  → coordinates the robot

RobotBrain
  → decides what the robot should do

Head
  → controls the robot's appearance

Animation
  → controls sprite animation

SpeechController
  → manages speech lifecycle

Speech
  → handles speech generation

Toy
  → represents interactive objects
```

The aim is to keep these systems independent enough that they can be
improved individually without rewriting the entire robot.

------------------------------------------------------------------------

## Current Development Direction

The immediate goal is to continue making Tingo feel alive rather than
simply adding isolated features.

Planned areas include:

### Behaviour

-   More autonomous idle behaviour
-   Better state transitions
-   Behaviour trees
-   Context-aware behaviour
-   More meaningful reactions to the environment

### Interaction

-   More interactive objects
-   Object recognition
-   Picking up and using objects
-   Reactions to different objects
-   More sophisticated interaction sequences

### Vision

-   Detecting objects in the environment
-   Understanding what Tingo is looking at
-   Using visual information as input to behaviour

### Memory

-   Remembering interactions
-   Short-term contextual memory
-   Longer-term character memory

### Voice

-   Speech recognition
-   Speech-to-text
-   Conversational interaction
-   More expressive speech behaviour

### Character

-   More emotions
-   More facial expressions
-   Dancing
-   Music
-   Guitar-related behaviours
-   Mini-games
-   Customisation

### Learning

-   Educational activities
-   Simple learning games
-   Interactive exercises

------------------------------------------------------------------------

## Long-Term Goal

The long-term goal is for TingoBingo to become more than a collection of
animations and scripted reactions.

The intended progression is:

``` text
Animated robot
      ↓
Interactive robot
      ↓
Reactive robot
      ↓
Behaviour-driven robot
      ↓
Context-aware robot
      ↓
Character
```

Tingo should eventually be able to observe what is happening, decide how
he feels about it, choose an appropriate behaviour, and express that
behaviour through movement, facial expression, interaction, and speech.

------------------------------------------------------------------------

## Development Approach

TingoBingo is being developed incrementally.

New systems are introduced in small pieces and tested before moving on
to the next layer.

The project deliberately favours understanding the underlying C++ and
system architecture over hiding complexity behind large frameworks.

When a system becomes complicated, the goal is to understand **why** it
is complicated and then simplify its responsibilities where possible.

------------------------------------------------------------------------

## Status

TingoBingo is an active development project.

The core robot, head animation, emotion system, interaction foundations,
and asynchronous speech pipeline are working foundations for the next
stage of development.

The project is still evolving rapidly, so this README describes the
current architecture and direction rather than a finished product.
