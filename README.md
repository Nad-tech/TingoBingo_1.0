# TingoBingo

TingoBingo is an interactive cardboard robot built with C++ and Raylib. Tingo can look around, respond to objects, express emotions, animate his face, and generate speech.

> **Status:** Active development. The project is currently a Windows desktop prototype.

## Features

- Modular robot made from independently controlled head and facial components
- Facial animation for eyes, pupils, eyebrows, mouth, ears, nose, and antenna
- Idle behaviours including blinking, head movement, and expressive feature animation
- Emotional states: neutral, happy, sad, angry, and surprised
- Autonomous searching after a period of inactivity
- Ray-based object detection using the same direction as Tingo's gaze
- Mouse interaction with draggable toys
- Current toys: ball and banana
- Speech generation and playback through Piper, FFmpeg, and Raylib audio
- Reusable sprite-sheet animation with frame ranges and animation priorities

## Controls

| Input | Action |
| --- | --- |
| Left Arrow | Turn Tingo left |
| Right Arrow | Turn Tingo right |
| Space | Trigger the current space-key interaction |
| H | Trigger the current H-key interaction |
| Left Mouse Button | Pick up and move an object |

The exact behaviour of keyboard interactions may change while the prototype is being developed.

## How It Works

The main loop is managed by `Game`:

```text
Initialise -> HandleInput -> Update -> Draw -> Shutdown
```

`RobotBrain` coordinates high-level behaviour. It manages idle, searching, and reacting states, then requests emotion, object, and speech actions from the relevant systems.

During a search, Tingo rotates his gaze and projects a 300-pixel ray into the scene. The ray is tested against registered object rectangles. When an object is found, Tingo focuses on it and can deliver an object-specific reaction.

Speech generation runs away from the game loop so Piper and FFmpeg processing does not block rendering. Raylib audio playback is kept on the main thread.

## Requirements

- Windows 10 or later
- [MSYS2](https://www.msys2.org/) with the MinGW 64-bit environment
- MinGW-w64 GCC/G++ and `mingw32-make`
- [Raylib](https://www.raylib.com/)
- Piper and FFmpeg for speech generation
- Git, if cloning the repository

The project is configured for the MSYS2 MinGW64 toolchain. Make sure the compiler, linker, Raylib libraries, and runtime DLLs are available in that environment.

## Build and Run

Open an MSYS2 MinGW64 terminal at the project root and run:

```bash
./scripts/build.sh
```

This compiles the source files with `mingw32-make` and launches `build/TingoBingo.exe`.

To build without launching the game:

```bash
mingw32-make
```

To remove compiled objects, dependency files, and the executable:

```bash
mingw32-make clean
```

To rebuild from scratch:

```bash
mingw32-make rebuild
```

### Visual Studio Code

The repository includes workspace settings, a build task, and a GDB launch configuration. With the C/C++ extension installed:

1. Press `Ctrl+Shift+B` to run the default build task.
2. Open **Run and Debug** and start the configured debug profile.

## Project Structure

```text
TingoBingo/
├── assets/       Images, audio, fonts, and speech resources
├── include/      Header files
├── src/          Application and gameplay implementation
│   ├── head/     Facial component implementations
│   └── body/     Body component implementations
├── scripts/      Build and project utility scripts
├── tools/        Local Piper and FFmpeg tools
├── Makefile      MinGW build configuration
└── build/        Generated build output
```

The `build/` directory and generated executables are ignored by Git. Source assets used by the application live under `assets/`; working files and render exports are excluded where appropriate.

## Architecture

```text
Game
├── Robot
│   ├── RobotBrain
│   │   ├── Behaviour and state management
│   │   ├── Emotion handling
│   │   ├── Searching and object detection
│   │   └── SpeechController
│   └── Head
│       ├── HeadBase
│       ├── Eyes and Pupils
│       ├── Eyebrows and Mouth
│       ├── Nose and Ears
│       └── Antenna
└── Objects
    ├── Ball
    └── Banana
```

The code is intentionally split into small systems so animation, behaviour, rendering, input, objects, and speech can evolve independently.

## Roadmap

- More object-specific reactions and activities
- More expressive and coordinated facial animations
- Expanded emotional transitions and emotion-driven behaviour
- Speech recognition and two-way voice interaction
- Memory, context-aware reactions, and a more distinct personality
- Mini-games, music interaction, dancing, and additional toys

## Contributing

This is an evolving personal project. Bug reports, ideas, and focused pull requests are welcome. Before making a larger change, describe the intended behaviour and keep new systems consistent with the existing modular architecture.

## License

No license has been declared for this repository yet. Please contact the author before redistributing the code or bundled assets.
