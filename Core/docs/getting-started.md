# Getting Started

This document explains the project in simple terms for someone who is still learning C or C++.

## 1. Header Files And Source Files

In this project, most declarations live in header files:

- `.h` files describe types, functions, and public APIs
- `.cpp` files contain the implementation

Example:

- `include/Core/Utils/Coordinator.h` tells you what the `Coordinator` can do
- `src/Utils/Coordinator.cpp` shows how it really works

If you come from C, think of headers as the public contract and source files as the executable logic behind that contract.

## 2. What Core Does

`Core` gives a game three main things:

- A game loop
- A rendering and audio backend through SDL
- An ECS architecture for gameplay data

It is a library, not a game by itself. `ArkaPong` uses `Core` to build a real executable.

## 3. Main Flow Of A Game Using Core

The typical flow is:

1. Call `Core::Init(...)`
2. Register scenes
3. Activate the first scene
4. Call `Core::Run()`

Inside the loop, Core:

- polls SDL events
- updates engine systems
- updates active scenes
- renders the frame

## 4. Important C++ Ideas Used Here

### Classes And Structs

Both exist in this codebase. In C++, `struct` and `class` are almost the same. The main difference is the default access level:

- `struct` defaults to `public`
- `class` defaults to `private`

Simple data containers such as `TransformComponent` are often `struct`s.

### References

You will often see `Type&`. That means "a reference to an existing object". It avoids copying and is safer than raw pointers in many situations.

### Raw Pointers

SDL APIs use raw pointers a lot:

- `SDL_Window*`
- `SDL_Renderer*`
- `SDL_Texture*`

Those pointers are valid only while the resource exists. This is why managers like `TextureManager` and `FontManager` matter.

### Smart Pointers

You will also see:

- `std::unique_ptr`
- `std::shared_ptr`

These are C++ ownership tools. They help avoid memory leaks by making ownership explicit.

## 5. How To Read A Feature

A practical workflow:

1. Open the public header first
2. Find where it is implemented
3. Find where it is used in `ArkaPong`

This is much easier than trying to understand the entire repo at once.
