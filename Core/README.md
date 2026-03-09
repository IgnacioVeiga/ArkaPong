# Core - Portable Game Engine

Core is a portable C++17 game engine library that provides essential infrastructure for 2D game development. It currently serves as the foundation for example projects such as `ArkaPong`.

## Features

- Entity Component System (ECS) architecture
- Project-level extension points for custom components and systems
- Resource management (textures, audio, fonts)
- Scene management system
- Input handling
- Physics and collision detection
- Audio system with BGM and SFX support
- Animation system
- Rendering pipeline
- Window management
- Configuration system

## Requirements

- C++17 compatible compiler
- SDL2 and related libraries (automatically managed by CMake)
- CMake 3.20 or higher

## Building

```bash
# From Core/
./build.sh  # Linux/macOS
# or
build.bat   # Windows CMD
# or
build.ps1   # PowerShell
```

## Integration

To use Core in your project:

1. Build the library
2. Copy the headers and built binaries to your project:
   ```
   your-project/
   ├── core_local/
   │   ├── include/  # Core headers
   │   └── lib/      # Link library + runtime files copied from Core/build
   ```
3. Build outputs are kept portable:
   - `build/lib/` -> `Core.lib`, `libCore.so`, `libCore.dylib`, `libCore.a`
   - `build/bin/` -> `Core.dll` on Windows
4. Consumer projects can either:
   - run their `copy_core.*` helper scripts, or
   - pass `-DCORE_INCLUDE_DIR=...` and `-DCORE_LIBRARY=...` to CMake directly

## Project Structure

- `include/Core/` - Public headers
  - `Component/` - ECS components
  - `Entity/` - Entity definitions
  - `Manager/` - Resource managers
  - `System/` - ECS systems
  - `Utils/` - Utility classes and functions
- `src/` - Implementation files
- `ThirdParty.cmake` - Dependency bootstrap

## Technical Details

- Modern C++17 features
- SDL2 for graphics, input, and audio
- Cross-platform support (Windows, Linux)
- Modular design for easy extension
- Smart pointer memory management
- Event-driven architecture

## Documentation

Start with [docs/README.md](docs/README.md) if you are new to this codebase or to C/C++ game-engine projects.

Key namespaces and classes:

- `Core::` - Main namespace
- `Core::Manager` - Resource management
- `Core::Component` - ECS components
- `Core::System` - Game systems
- `Core::Entity` - Game entities
- `Core::Utils` - Helper utilities

The recommended way to extend the engine from a game project is documented in `docs/ecs-development.md`. You do not need to edit `Core` to add your own components or systems.
