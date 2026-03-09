# Configuration And Scenes

This document focuses on two practical systems: config files and scenes.

## 1. Configuration

`Core` reads a JSON file and merges it with default values.

Today the config is used for:

- logical resolution
- window size options
- fullscreen and borderless flags
- VSync
- audio setup
- some gameplay data consumed by `ArkaPong`

This is important because it moves tuning out of hardcoded constants and into data.

## 2. Scenes In This Project

A scene is a group of entities that belong together, such as:

- title menu
- round gameplay
- pause menu

Each entity stores its `scene_name` inside `BaseComponent`.

`SceneManager` controls which scene objects are active, while `Coordinator` can now serialize and deserialize scene data using that same `scene_name`.

## 3. Scene Serialization

`Coordinator` can now:

- serialize one entity
- deserialize one entity
- serialize a full scene
- save a scene to disk
- load a scene from disk

The scene JSON format is intentionally simple:

```json
{
  "scene_name": "Round",
  "entities": [
    {
      "BaseComponent": {
        "entity_name": "Ball",
        "scene_name": "Round"
      }
    }
  ]
}
```

The exact component set can be larger, but the idea stays the same.

## 4. What Is Not Serialized Yet

Not every component is a good candidate for plain JSON serialization.

Examples:

- `InputComponent` stores callbacks
- some path behaviors depend on runtime polymorphism
- SDL pointers are runtime resources, not stable file data

That means scene serialization is currently best used for data-oriented content. Runtime-only behavior still needs explicit code setup.

## 5. Why This Matters For The MVP

This is a step toward:

- scene templates
- simple content tools
- future save/load support
- a lightweight editor workflow

Even before a full editor exists, scene files are already useful as a stable content boundary.

## 6. Good Next Experiments

- Save a simple scene to JSON
- Load it into an empty scene name
- Compare the saved file with the entity/component state in code
- Extend serialization with one more component when needed
