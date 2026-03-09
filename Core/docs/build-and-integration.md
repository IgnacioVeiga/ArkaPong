# Build And Integration

This guide explains how to build `Core` and how other projects consume it.

## 1. Build System

The project uses CMake.

CMake does not compile your code directly. It generates build files for your platform and compiler.

Examples:

- Visual Studio projects on Windows
- Makefiles or Ninja files on Linux

## 2. Why Core Is Portable

For now, `Core` is meant to be copied into another project instead of being installed system-wide.

That is why the build is organized around:

- `build/lib`
- `build/bin`

Consumer projects can copy:

- public headers into `core_local/include`
- link/runtime binaries into `core_local/lib` and `core_local/bin` when needed

## 3. Dependency Strategy

`Core` uses SDL libraries:

- SDL2
- SDL2_mixer
- SDL2_ttf

The CMake setup tries these sources in order:

1. local third-party binaries
2. system packages
3. `FetchContent`

This keeps the repo easier to start with, especially on fresh machines.

## 4. Shell Scripts And Platform-Specific Files

The repository includes multiple helper scripts:

- `.bat` for Windows Command Prompt
- `.ps1` for PowerShell
- `.sh` for Bash-compatible shells

The `.sh` scripts now resolve Core binaries by host platform. That means Linux and macOS no longer look for Windows DLLs, while Git Bash or MSYS on Windows can still use them.

## 5. Recommended Beginner Workflow

1. Build `Core`
2. Build `ArkaPong` against that `Core`
3. Change one config value
4. Rebuild and observe the effect

That loop teaches the project faster than reading everything first.
