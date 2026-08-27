# TingoBingo

TingoBingo is a modular C++20/Raylib virtual cardboard robot.

The project started as a simple animated robot and is gradually becoming
a small interactive character with its own behaviour, emotions, facial
animation, speech, object interaction, and eventually more autonomous
behaviour.

The goal is not to build a generic game framework. The goal is to build
**Tingo** — a character whose systems work together to make him feel alive.

------------------------------------------------------------------------

## Current Features

### Robot Architecture

Tingo is split into several cooperating systems:

- `Robot` — the main interface for the robot.
- `RobotBrain` — controls behaviour and high-level state.
- `Head` — coordinates the visual components of the head.
- `Animation` — provides reusable sprite-sheet animation.
- `Emotion` — defines Tingo's high-level emotional states.
- `SpeechController` — manages asynchronous speech generation and playback.
- `Speech` — handles Piper and FFmpeg speech generation.
- `Toy` — provides interactive objects that Tingo can pick up and manipulate.

The general relationship is:

```text
                    Robot
                   /     \
                  /       \
          RobotBrain       Head
              |              |
          Behaviour      Facial features
              |              |
           Speech       Eyes / Mouth /
                        Eyebrows / Pupils /
                        Nose / Ears / Antenna