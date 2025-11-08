# Frontend - Development Tools

Frontend is a collection of development and debugging tools for the ArkaPong game engine and core library. It provides a graphical interface for testing, debugging, and content creation.

## Features

- ImGui-based development interface
- Real-time component inspection
- Scene hierarchy viewer
- Resource manager interface
- Performance monitoring
- Audio testing tools
- Level editor interface

## Requirements

- C++17 compatible compiler
- SDL2 libraries (managed by CMake)
- Core library
- Dear ImGui (included in ThirdParty)

## Quick Start

If you have the Core source repository locally:

```bash
# From Frontend/
./copy_core.sh /path/to/Core
./build.sh
./run.sh
```

If you have a prebuilt Core library, place its headers and library inside `Frontend/core_local/`:

- `core_local/include/` -> Core headers
- `core_local/lib/` -> compiled Core library (libCore.so / Core.dll)

Then run:

```bash
./build.sh
./run.sh
```

## Technical Details

- Built with modern C++17
- Dear ImGui integration for UI
- Direct access to Core library internals
- Cross-platform support (Windows, Linux)
- CMake build system

## Project Structure

- `src/` - Source code
  - `main.cpp` - Application entry point
- `ThirdParty/` - External dependencies
  - `imgui-docking/` - Dear ImGui with docking support

## Building

Build scripts are available for multiple platforms:
- Linux/macOS: `build.sh`, `run.sh`
- Windows CMD: `build.bat`, `run.bat`
- PowerShell: `build.ps1`, `run.ps1`

## Usage Guide

### Resource Management
- Load and preview textures
- Test audio files
- Manage font resources

### Development Tools
- Entity inspector
- Component editor
- Scene hierarchy viewer
- Performance metrics

### Debug Features
- Real-time variable inspection
- System state monitoring
- Resource usage tracking
- Frame timing analysis

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request
