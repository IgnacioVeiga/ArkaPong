#pragma once

#include <algorithm>
#include <functional>

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>

#include "Core/Component/InputComponent.h"
#include "Core/Component/RigidBodyComponent.h"
#include "Core/Component/SpriteComponent.h"
#include "Core/Component/TransformComponent.h"
#include "Core/Manager/TextureManager.h"
#include "Core/Utils/CoreConstants.h"

inline auto paddleCollisionCallback = [](Entity self, Entity other) {
    // TODO: do collision logic with walls, enemies or something like that.
};

inline auto goUpCallback = [](const Entity self) {
    auto &transformComponent = Core::GetCoordinator().GetComponent<TransformComponent>(self);
    const auto &rigidBodyComponent = Core::GetCoordinator().GetComponent<RigidBodyComponent>(self);

    transformComponent.position.y = std::max(0.0f, transformComponent.position.y - rigidBodyComponent.velocity.y);
};

inline auto goDownCallback = [](const Entity self) {
    auto &transformComponent = Core::GetCoordinator().GetComponent<TransformComponent>(self);
    const auto &rigidBodyComponent = Core::GetCoordinator().GetComponent<RigidBodyComponent>(self);

    transformComponent.position.y = std::min(static_cast<float>(GetGameHeight() - GetPaddleHeight()),
                                             transformComponent.position.y + rigidBodyComponent.velocity.y);
};

inline void CreatePaddleEntity(const std::string &entity_name, const std::string &scene_name, const Side side) {
    const int paddleWidth = GetPaddleWidth();
    const int paddleHeight = GetPaddleHeight();
    const float paddleSpeed = GetPaddleSpeed();
    const int gameWidth = GetGameWidth();
    const int gameHeight = GetGameHeight();
    SDL_Texture *texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);
    constexpr SDL_Rect srcRectPaddle = {
        0, // X
        0, // Y
        DEFAULT_PADDLE_WIDTH, // W
        DEFAULT_PADDLE_HEIGHT // H
    };

    const int x_position = (side == Side::LEFT) ? PADDLE_OFFSET : (gameWidth - PADDLE_OFFSET - paddleWidth);
    const SDL_RendererFlip flip = (side == Side::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    std::vector<InputBehavior> keyMappings;
    const auto addMapping = [&keyMappings](SDL_Scancode scancode, SDL_Keycode keycode,
                                           const std::function<void(Entity)> &callback) {
        if (scancode == SDL_SCANCODE_UNKNOWN && keycode == SDLK_UNKNOWN) {
            return;
        }
        const auto exists = std::find_if(
            keyMappings.begin(),
            keyMappings.end(),
            [scancode, keycode](const InputBehavior &mapping) {
                return mapping.scancode == scancode && mapping.keycode == keycode;
            });
        if (exists == keyMappings.end()) {
            keyMappings.push_back({scancode, keycode, callback});
        }
    };

    if (side == Side::LEFT) {
        // Layout-aware letter mappings (keycode-driven).
        addMapping(SDL_SCANCODE_UNKNOWN, SDLK_w, goUpCallback);
        addMapping(SDL_SCANCODE_UNKNOWN, SDLK_s, goDownCallback);
        addMapping(SDL_SCANCODE_UNKNOWN, SDLK_z, goUpCallback);
    } else {
        addMapping(SDL_SCANCODE_UP, SDLK_UP, goUpCallback);
        addMapping(SDL_SCANCODE_DOWN, SDLK_DOWN, goDownCallback);
    }

    const auto velocity = Vec2(0, paddleSpeed);

    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(
        entity,
        TransformComponent{
            Vec2(static_cast<float>(x_position),
                 static_cast<float>(gameHeight) / 2.0f - static_cast<float>(paddleHeight) / 2.0f)
        });
    Core::GetCoordinator().AddComponent(
        entity,
        SpriteComponent{
            texture, // Texture
            srcRectPaddle, // Source rectangle
            {
                // Destination rectangle
                0, // X
                0, // Y
                static_cast<float>(paddleWidth), // W
                static_cast<float>(paddleHeight) // H
            },
            flip,
            VAUS_SPRITE_FILEPATH
        });
    Core::GetCoordinator().AddComponent(
        entity,
        RigidBodyComponent{
            {0, 0, static_cast<float>(paddleWidth), static_cast<float>(paddleHeight)}, // Collider
            velocity,
            Vec2(0, 0), // Acceleration
            1.0f, // Mass
            true, // Static? Yes, because it only moves vertically
            false, // Use gravity?
            paddleCollisionCallback
        });
    Core::GetCoordinator().AddComponent(
        entity,
        InputComponent{keyMappings, 5});
}
