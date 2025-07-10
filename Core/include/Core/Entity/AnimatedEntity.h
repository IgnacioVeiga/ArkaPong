#pragma once

#include <SDL2/SDL_render.h>
#include <string>
#include "Core/Core.h"
#include "Core/Manager/TextureManager.h"
#include "Core/Component/TransformComponent.h"
#include "Core/Component/SpriteComponent.h"
#include "Core/Component/AnimationComponent.h"
#include "Core/Component/PathComponent.h"

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
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);

    SDL_Texture *texture = TextureManager::LoadTexture(texturePath.c_str());
    Core::GetCoordinator().AddComponent(
        entity,
        TransformComponent{pos});
    Core::GetCoordinator().AddComponent(
        entity,
        SpriteComponent{
            texture,
            {0, 0, frameWidth, frameHeight}, // Source rectangle
            {0, 0, static_cast<float>(frameWidth), static_cast<float>(frameHeight)},
            SDL_FLIP_NONE
        });

    Core::GetCoordinator().AddComponent(
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

    Core::GetCoordinator().AddComponent(entity, PathComponent{movementScript, events});
}
