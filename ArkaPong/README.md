# ArkaPong

ArkaPong is a modern take on the classic Arkanoid/Breakout game genre, featuring both single-player and two-player modes. Built with C++ and SDL2, it combines retro gameplay with modern programming practices.

## Features

- Classic brick-breaking gameplay with modern graphics
- Two-player mode with paddles on both sides
- Dynamic ball physics and paddle controls
- Retro-style sound effects and background music
- Multiple brick types and level designs
- Animated sprites and particle effects
- Configurable controls and settings

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
- `src/` - Source code
  - `Entities/` - Game entity definitions
  - `Scenes/` - Game scene management
  - `Utils/` - Utility functions and constants
- `cmake/` - Build system configuration

## License

This project is available under the MIT License. See the LICENSE file for more details.