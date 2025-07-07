#pragma once

#include <functional>
#include "Core/Manager/TextureManager.h"

inline auto paddleCollisionCallback = [](Entity self, Entity other) {
    // TODO: do collision logic with walls, enemies or something like that.
};

inline auto goUpCallback = [](const Entity self) {
    auto &transformComponent = Core::coordinator.GetComponent<TransformComponent>(self);
    const auto &rigidBodyComponent = Core::coordinator.GetComponent<RigidBodyComponent>(self);

    transformComponent.position.y = std::max(0.0f, transformComponent.position.y - rigidBodyComponent.velocity.y);
};

inline auto goDownCallback = [](const Entity self) {
    auto &transformComponent = Core::coordinator.GetComponent<TransformComponent>(self);
    const auto &rigidBodyComponent = Core::coordinator.GetComponent<RigidBodyComponent>(self);

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

    const SDL_Keycode upKeyCode = (side == Side::LEFT) ? SDL_SCANCODE_W : SDL_SCANCODE_UP;
    const SDL_Keycode downKeyCode = (side == Side::LEFT) ? SDL_SCANCODE_S : SDL_SCANCODE_DOWN;

    const std::vector<InputBehavior> keyMappings = {
        {upKeyCode, goUpCallback},
        {downKeyCode, goDownCallback}
    };

    const auto velocity = Vec2(0, PADDLE_SPEED);

    const Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);
    Core::coordinator.AddComponent(
        entity,
        TransformComponent{
            Vec2(static_cast<float>(x_position),
                 static_cast<float_t>(SCREEN_HEIGHT) / 2 - static_cast<float_t>(PADDLE_HEIGHT) / 2)
        });
    Core::coordinator.AddComponent(
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
    Core::coordinator.AddComponent(
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
    Core::coordinator.AddComponent(
        entity,
        InputComponent{keyMappings, 5});
}
