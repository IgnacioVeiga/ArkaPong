# ECS Development

This guide is for contributors who want to add gameplay or engine features by following the ECS style already used in `Core`.

## 1. The Practical Rule

When adding a new feature, ask three questions:

1. What data must exist on an entity?
2. What logic should process that data?
3. Does the feature need reusable creation helpers?

The answers usually map to:

1. a component
2. a system
3. an entity helper

## 2. Adding A Component

Create a new component when you need persistent data attached to an entity.

Good examples:

- health
- damage
- particle lifetime
- AI state

Bad examples:

- huge classes that mix data and rendering
- components that mostly exist to hide one giant callback

Components in this project are intentionally simple `struct`s.

## 3. Adding A System

Create a system when multiple entities need the same logic.

Examples already in the engine:

- `SpriteSystem`
- `PhysicsSystem`
- `TextSystem`
- `InputSystem`

A system should:

- declare the component signature it needs
- iterate matching entities
- keep logic focused on one responsibility

If one system starts doing rendering, physics, audio, and scene control all together, it is probably too broad.

## 4. Registering New ECS Types

This project wires common engine components and systems inside `BaseSystem`.

The usual workflow is:

1. define the component
2. register the component from the game or engine bootstrap code
3. create and initialize the system from the same bootstrap point
4. add the component to entities that should participate

`BaseSystem` is for engine-owned defaults. Game-specific ECS types should be registered through `Core::AddInitCallback(...)` so you do not need to edit the engine.

## 5. Entity Helpers

Entity helper functions are used to create reusable setups such as:

- text entities
- background entities
- audio entities
- animated entities

They are useful when the same component bundle appears often.

For example, an input-only menu action can still be represented as an entity. That is why `Core` now provides an input entity helper instead of requiring scenes to poll SDL directly for every transition.

## 6. Data Components Versus Runtime Components

This distinction matters a lot.

### Data-oriented components

These are easier to serialize and edit:

- transform
- sprite rectangles
- colors
- text values
- physics numbers

### Runtime-only components

These need extra care:

- callbacks stored in `std::function`
- SDL pointers
- polymorphic path objects

If a component contains runtime-only state, do not assume it belongs in JSON as-is.

## 7. A Safe Development Pattern

When you add a feature:

1. start with the smallest possible component
2. write the system that consumes it
3. create one entity helper only if repetition appears
4. decide explicitly whether the component is serializable

This keeps the engine from drifting into tightly coupled code.

## 8. ArkaPong As Example Code

`ArkaPong` should act as an example game, not as a second engine.

That means game code should prefer:

- using existing engine systems
- grouping behavior through components
- using helper entities for repeated setups

and avoid:

- bypassing ECS for common gameplay flow
- hardcoding too much engine behavior inside scene update functions

## 9. Good Questions Before Merging A Feature

- Is the data model small and clear?
- Does the logic belong in an existing system or a new one?
- Can this be configured instead of hardcoded?
- Should this be serializable?
- Would another game be able to reuse this?

## 10. Extending Core From A Game Project

`Core` now exposes lifecycle hooks so a game can register its own ECS types without modifying engine code.

The usual extension flow is:

1. define your component in the game project
2. define your system in the game project
3. register both through `Core::AddInitCallback(...)`
4. update the system through `Core::AddUpdateCallback(...)`

Example:

```cpp
struct HealthComponent
{
    int current = 3;
    int max = 3;
};

class HealthSystem : public System
{
public:
    void Init()
    {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<HealthComponent>());
        Core::GetCoordinator().SetSystemSignature<HealthSystem>(signature);
    }

    void Update(float delta_time)
    {
        for (const Entity entity : mEntities)
        {
            auto& health = Core::GetCoordinator().GetComponent<HealthComponent>(entity);
            // Game-specific logic goes here.
        }
    }
};

int main()
{
    Core::AddInitCallback([]()
    {
        auto& coordinator = Core::GetCoordinator();
        coordinator.RegisterComponent<HealthComponent>();
        coordinator.RegisterSystem<HealthSystem>()->Init();
    });

    Core::AddUpdateCallback([](float delta_time)
    {
        if (auto system = Core::GetCoordinator().GetSystem<HealthSystem>())
        {
            system->Update(delta_time);
        }
    });

    Core::Init("config.json", "My Game");
    Core::Run();
}
```

This is the intended project-level customization path. If you can solve a problem this way, do that before changing the engine itself.
