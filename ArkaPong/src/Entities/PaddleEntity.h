#pragma once

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

    transformComponent.position.y = std::min(static_cast<float>(SCREEN_HEIGHT - PADDLE_HEIGHT),
                                             transformComponent.position.y + rigidBodyComponent.velocity.y);
};

inline void CreatePaddleEntity(const std::string &entity_name, const std::string &scene_name, const Side side) {
    SDL_Texture *texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);
    constexpr SDL_Rect srcRectPaddle = {
        0, // X
        0, // Y
        PADDLE_WIDTH, // W
        PADDLE_HEIGHT // H
    };

    const int x_position = (side == Side::LEFT) ? PADDLE_OFFSET : (SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH);
    const SDL_RendererFlip flip = (side == Side::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

    SDL_Scancode upScancode = SDL_SCANCODE_UP;
    SDL_Scancode downScancode = SDL_SCANCODE_DOWN;
    if (side == Side::LEFT) {
        // Use the active keyboard layout for letter controls (W/S equivalent).
        upScancode = SDL_GetScancodeFromKey(SDLK_w);
        downScancode = SDL_GetScancodeFromKey(SDLK_s);

        // Fallback for platforms/layouts that fail to map keycodes.
        if (upScancode == SDL_SCANCODE_UNKNOWN) {
            upScancode = SDL_SCANCODE_W;
        }
        if (downScancode == SDL_SCANCODE_UNKNOWN) {
            downScancode = SDL_SCANCODE_S;
        }
    }

    const std::vector<InputBehavior> keyMappings = {
        {upScancode, goUpCallback},
        {downScancode, goDownCallback}
    };

    const auto velocity = Vec2(0, PADDLE_SPEED);

    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(
        entity,
        TransformComponent{
            Vec2(static_cast<float>(x_position),
                 static_cast<float_t>(SCREEN_HEIGHT) / 2 - static_cast<float_t>(PADDLE_HEIGHT) / 2)
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
                PADDLE_WIDTH, // W
                PADDLE_HEIGHT // H
            },
            flip
        });
    Core::GetCoordinator().AddComponent(
        entity,
        RigidBodyComponent{
            {0, 0, PADDLE_WIDTH, PADDLE_HEIGHT}, // Collider
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
