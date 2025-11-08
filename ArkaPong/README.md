# ArkaPong

ArkaPong is a unique fusion of classic Arkanoid and Pong gameplay mechanics, featuring both single-player and two-player modes. Built with C++ and SDL2, it combines retro gameplay with modern programming practices.

## Game Concept

ArkaPong combines elements from two classic games:

### Arkanoid/Breakout
![Arkanoid](https://images.squarespace-cdn.com/content/v1/5e004a01af59914152deea6d/1604237320287-Q5RPEEJ8B77OTM4OSGXV/Brick+Breaker.gif)

### Pong
![PONG](https://www.retrogames.cz/games/530/Pong-gameplay.gif)

Creating a unique hybrid gameplay experience:
![ArkaPong](https://github.com/user-attachments/assets/538974f9-4e3c-4382-9c7e-d15dc1607d17)

## Features

- Classic brick-breaking gameplay with modern graphics
- Two-player mode with paddles on both sides
- Dynamic ball physics and paddle controls
- Retro-style sound effects and background music
- Multiple brick types and level designs
- Animated sprites and particle effects
- Configurable controls and settings
- Level editor support through text files

## Requirements

- C++17 compatible compiler
- SDL2 libraries (automatically managed by CMake)
- Core library (included or built separately)

## Quick Start

If you have the Core source repository locally:

```bash
# From ArkaPong/
./copy_core.sh /path/to/Core
./build.sh
./run.sh
```

If you only have a prebuilt Core library, place its headers and library inside `ArkaPong/core_local/` with the following layout:

- `core_local/include/` -> Core headers
- `core_local/lib/` -> compiled Core library (libCore.so / Core.dll)

Then run:

```bash
./build.sh
./run.sh
```

## Controls

- Left Player: W/S keys for up/down movement
- Right Player: Up/Down arrow keys
- Backspace: Return to title screen
- ESC: Exit game

## Technical Details

- Built with modern C++17
- Entity Component System (ECS) architecture
- Portable game engine core
- Cross-platform support (Windows, Linux)
- CMake build system
- SDL2 rendering and audio

## Building

Build scripts are available for multiple platforms:
- Linux/macOS: `build.sh`, `run.sh`
- Windows CMD: `build.bat`, `run.bat`
- PowerShell: `build.ps1`, `run.ps1`

SDL2 dependencies are managed automatically by the `cmake/ThirdParty.cmake` script.

## Project Structure

- `assets/` - Game resources (sprites, audio, fonts, levels)
  - `audio/` - Sound effects and background music
  - `fonts/` - Game fonts
  - `levels/` - Level design files
  - `sprites/` - Game graphics and animations
- `src/` - Source code
  - `Entities/` - Game entity definitions
  - `Scenes/` - Game scene management
  - `Utils/` - Utility functions and constants
- `cmake/` - Build system configuration

## Creating Custom Levels

Levels are defined in text files under `assets/levels/`. Each level file follows this format:
```
rows columns
[grid of numbers representing brick types]
```

Example:
```
6 8
1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 2
3 3 3 3 3 3 3 3
1 1 1 1 1 1 1 1
2 2 2 2 2 2 2 2
3 3 3 3 3 3 3 3
```
