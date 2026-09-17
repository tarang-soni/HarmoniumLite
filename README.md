# HarmoniumLite

A lightweight virtual harmonium built in C++ and SFML. Play Indian classical notes
(Sa Re Ga Ma Pa Dha Ni) directly on your keyboard, shift octaves, and enjoy
procedurally synthesized piano-like tones — no audio samples required.

<!-- Add a project banner/logo here -->
![HarmoniumLite Banner](docs/images/banner.png)

## About

HarmoniumLite (internally the `MusicGame` project, in-game title *Sasta Harmonium*)
is a keyboard-playable harmonium/piano. It maps the white and black keys of a piano
layout onto the keyboard and synthesizes each note in real time using additive
harmonic synthesis, so the entire instrument runs with zero pre-recorded audio files.

## Features

- **Keyboard playable** — play notes with the `Z`–`M` row (major) and `S D G H J` (minor)
- **Octave shifting** — move up/down octaves, or temporarily jump an octave with `Shift`
- **Procedural audio** — piano-like tones generated at startup (`PianoSoundGenerator.h`)
- **JSON-driven UI** — menus, buttons, text, colors, and callbacks defined in `resources/example.json`
- **State-machine architecture** — `StateStack`-based scene management
- **Fully static build** — single `.exe` with statically linked MinGW runtime and SFML

## Screenshots

<!-- Add a screenshot of the main menu here -->
![Main Menu](docs/images/menu.png)

<!-- Add a screenshot of the game / harmonium screen here -->
![Game Screen](docs/images/game.png)

## Controls

### Notes (major keys)

| Key | Note |
|-----|------|
| `Z` | Sa |
| `X` | Re |
| `C` | Ga |
| `V` | Ma |
| `B` | Pa |
| `N` | Dha |
| `M` | Ni |

### Notes (minor / komal & tivra keys)

| Key | Note      |
|-----|-----------|
| `S` | re (komal)|
| `D` | ga (komal)|
| `G` | Ma (tivra)|
| `H` | dha (komal)|
| `J` | ni (komal)|

### System controls

| Control              | Action                                     |
|----------------------|--------------------------------------------|
| `Up Arrow`           | Raise octave (up to octave 6)              |
| `Down Arrow`         | Lower octave (down to octave 1)            |
| `Left Shift` (hold)  | Temporarily raise one octave               |
| `Left Shift` (release)| Return to the original octave              |
| Mouse (left click)   | Click a key to play / release to stop      |

## Requirements

- **CMake** 3.16 or newer
- **C++17** compiler (MinGW-w64 recommended on Windows)
- **Internet connection** on first configure (SFML is fetched via `FetchContent`)

## Building

The project fetches and builds SFML 2.6.2 automatically and links everything
statically. `nlohmann/json` is bundled locally in `dir/include`.

```powershell
# From the project root
cmake -S MusicGame/MusicGame -B build -G "MinGW Makefiles"
cmake --build build
```

The built executable (`MusicGame.exe`) will be placed in the build directory, with
the `resources/` folder copied alongside it automatically.

## Project Structure

```
MusicGame/
├── MusicGame/
│   ├── CMakeLists.txt          # Build configuration (SFML via FetchContent)
│   ├── resources/
│   │   ├── example.json        # Data-driven UI definition
│   │   ├── Roboto-Medium.ttf   # Font used by the UI
│   │   └── Roboto-Thin.ttf
│   └── src/
│       ├── Main.cpp            # Entry point (hides console in release)
│       ├── Game.h / .cpp       # Main loop, window, StateStack owner
│       ├── StateStack.h / .cpp # State management (push/pop/clear)
│       ├── State.h             # Abstract State interface + Context
│       ├── StateIdentifiers.h  # States::ID enum
│       ├── MenuState.h / .cpp  # Main menu screen
│       ├── GameState.h / .cpp  # Game / instrument screen
│       ├── Scene.h / .cpp      # Holds the music keys, buffers, and sounds
│       ├── MusicKey.h / .cpp   # A single playable key (major/minor)
│       ├── PianoSoundGenerator.h # Procedural audio synthesis
│       ├── Scales.h            # 12-note frequency ratios
│       ├── KeyContext.h        # Shared audio/key context passed to keys
│       ├── Entity.h / .cpp     # Composite base (scene graph)
│       ├── GameObject.h / .cpp # Drawable + Transformable entity
│       ├── UIFactory.h / .cpp  # Creates UI elements from JSON
│       ├── UIElement.h / .cpp  # UI element base class
│       ├── Button.h / .cpp     # Button element with hover/press states
│       ├── Text.h / .cpp       # Text element
│       ├── UIProperties.h / .cpp # UIType enum
│       ├── CallbackRegistry.h  # Maps callback names to member functions
│       ├── FontDictionary.h    # Font registry helper
│       └── Core.h              # Color parsing utility + constants
└── dir/
    └── include/nlohmann/       # Bundled nlohmann/json
```

## Configuration

The UI is fully data-driven via `resources/example.json`. Each screen (`Menu`,
`Game`) defines a background color and a list of UI elements.

```json
{
  "Menu": {
    "bgColor": "#552200",
    "uiElements": [
      {
        "type": "Text",
        "id": "welcomeText",
        "fontFamily": "Roboto-Medium",
        "fontSize": 30,
        "textColor": "#FFFFFF",
        "position": { "x": 400, "y": 50 },
        "content": "Welcome to the Sasta Harmonium!"
      },
      {
        "type": "Button",
        "id": "startButton",
        "fontFamily": "Roboto-Medium",
        "fontSize": 20,
        "textColor": "#000000",
        "buttonStateColors": {
          "Default": "#FFFFFF",
          "Hover": "#FFFF00",
          "Pressed": "#FF0000"
        },
        "position": { "x": 400, "y": 300 },
        "size": { "width": 150, "height": 50 },
        "content": "Start",
        "callback": "StartGame"
      }
    ]
  }
}
```

Supported element types:

| Type     | Description                                        |
|----------|----------------------------------------------------|
| `Text`   | A styled text label (font, size, color, position)  |
| `Button` | A clickable button with default/hover/pressed colors and a `callback` name |

Button `callback` values map to member functions registered via
`CallbackRegistry` in the owning state (e.g. `StartGame`, `MainMenu`).

## Dependencies

- [SFML 2.6.2](https://www.sfml-dev.org/) — graphics, windowing, and audio
- [nlohmann/json](https://github.com/nlohmann/json) — JSON parsing (bundled)

## License

<!-- Add license information here (no license file is currently present in the repository) -->

Distributed under the [Your License] license. See `LICENSE` for more information.
