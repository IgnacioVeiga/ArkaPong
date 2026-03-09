# Core Docs

This folder is a beginner-friendly guide to the `Core` project.

If you already know modern C++, you can skim these files. If you are still getting used to headers, source files, pointers, CMake, or engine architecture, read them in order.

## Reading Order

1. [Getting Started](getting-started.md)
2. [Build And Integration](build-and-integration.md)
3. [Engine Concepts](engine-concepts.md)
4. [ECS Development](ecs-development.md)
5. [Configuration And Scenes](configuration-and-scenes.md)

## What Core Is

`Core` is a small portable 2D engine library written in C++17. It is not meant to be a full Unity or Godot replacement. The goal is to provide a compact base that is easy to understand, extend, and use from example projects like `ArkaPong`.

## What You Should Learn First

- How a `.h` header differs from a `.cpp` source file
- How CMake generates builds for different platforms
- How SDL handles windows, rendering, input, and audio
- How this project uses ECS: entities, components, and systems
- How a game can register its own components and systems without changing `Core`
- How scenes and config files are represented

## Good First Files To Read

- `include/Core/Core.h`
- `src/Core.cpp`
- `include/Core/Utils/Coordinator.h`
- `src/Utils/Coordinator.cpp`
- `include/Core/System/BaseSystem.h`
- `src/Utils/Window.cpp`

## Practical Tip

When a type or function feels confusing, search for both its declaration and its implementation. In C/C++ projects, understanding usually comes from reading the header and the source together.
