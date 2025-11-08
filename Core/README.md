# Core - Portable Game Engine

Core is a portable C++17 game engine library that provides essential infrastructure for 2D game development. It serves as the foundation for both ArkaPong game and Frontend tools.

## Features

- Entity Component System (ECS) architecture
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
- CMake 3.0 or higher

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
2. Copy the headers and built library to your project:
   ```
   your-project/
   ├── core_local/
   │   ├── include/  # Core headers
   │   └── lib/      # Built library (libCore.so/Core.dll)
   ```
3. Link against Core in your CMake:
   ```cmake
   find_package(Core REQUIRED)
   target_link_libraries(YourTarget PRIVATE Core)
   ```

## Project Structure

- `include/Core/` - Public headers
  - `Component/` - ECS components
  - `Entity/` - Entity definitions
  - `Manager/` - Resource managers
  - `System/` - ECS systems
  - `Utils/` - Utility classes and functions
- `src/` - Implementation files
- `cmake/` - CMake configuration files

## Technical Details

- Modern C++17 features
- SDL2 for graphics, input, and audio
- Cross-platform support (Windows, Linux)
- Modular design for easy extension
- Smart pointer memory management
- Event-driven architecture

## Documentation

Key namespaces and classes:

- `Core::` - Main namespace
- `Core::Manager` - Resource management
- `Core::Component` - ECS components
- `Core::System` - Game systems
- `Core::Entity` - Game entities
- `Core::Utils` - Helper utilities

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request
