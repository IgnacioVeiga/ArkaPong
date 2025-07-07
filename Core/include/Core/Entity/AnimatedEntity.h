#pragma once

#include <SDL2/SDL_render.h>
#include <string>
#include "../include/Core/Core.h"
#include "../Manager/TextureManager.h"
#include "../Component/TransformComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/AnimationComponent.h"
#include "../Component/PathComponent.h"

inline void CreateAnimatedEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const std::string &texturePath,
    const int frameCount,
    const int frameWidth,
    const int frameHeight,
    const int animationSpeed,
    const bool loop,
    const Vec2 pos
) {
    const Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);

    SDL_Texture *texture = TextureManager::LoadTexture(texturePath.c_str());
    Core::coordinator.AddComponent(
        entity,
        TransformComponent{pos});
    Core::coordinator.AddComponent(
        entity,
        SpriteComponent{
            texture,
            {0, 0, frameWidth, frameHeight}, // Source rectangle
            {0, 0, static_cast<float>(frameWidth), static_cast<float>(frameHeight)},
            SDL_FLIP_NONE
        });

    Core::coordinator.AddComponent(
        entity,
        AnimationComponent{
            0, // currentFrame
            frameCount,
            frameWidth,
            frameHeight,
            animationSpeed,
            0, // elapsedTime
            loop,
            true // isPlaying
        });

    const std::shared_ptr<BasePath> movementScript = std::make_shared<CircularPath>(
        (SCREEN_WIDTH / 2.0f) - 8.0f, // Center X
        (SCREEN_HEIGHT / 2.0f) - 8.0f, // Center Y
        64.0f, // Radius
        1.0f // Speed
    );

    const std::vector<PathEvent> events = {};

    Core::coordinator.AddComponent(entity, PathComponent{movementScript, events});
}
