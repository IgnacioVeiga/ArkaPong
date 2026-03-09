# Engine Concepts

This file explains the main architecture in plain English.

## 1. ECS Basics

ECS means:

- Entity: an ID
- Component: data attached to that ID
- System: logic that runs on entities matching a component set

In this project:

- `Entity` is just an integer-like identifier
- `TransformComponent`, `SpriteComponent`, `RigidBodyComponent`, and similar types hold data
- `SpriteSystem`, `PhysicsSystem`, `AudioSystem`, and others process that data

## 2. Why Use ECS Here

For a small engine, ECS keeps gameplay code modular:

- rendering does not need to know audio details
- physics can run on entities that have rigid bodies
- text rendering only touches text entities

That separation is one of the most important design ideas in `Core`.

## 3. The Coordinator

`Coordinator` is the main ECS entry point.

It knows how to:

- create and destroy entities
- add and remove components
- register and query systems
- serialize entities and scenes

If you are unsure where gameplay data enters the engine, start with `Coordinator`.

## 4. Systems Registered By Default

`BaseSystem` wires up the common systems:

- input
- sprite rendering
- audio
- text
- backgrounds
- animation
- paths
- physics

This keeps `Core::Init(...)` relatively small while still preparing the engine for a typical 2D game.

## 5. Resources

Textures, fonts, and audio are cached by managers.

Why this matters:

- loading the same file every frame would be too slow
- ownership must stay consistent
- SDL resources need explicit cleanup

## 6. Typical Example

A brick in `ArkaPong` is not a custom brick class with lots of behavior. It is mostly:

- a transform
- a sprite
- a rigid body
- a base component with metadata

That is the ECS mindset used throughout the project.
