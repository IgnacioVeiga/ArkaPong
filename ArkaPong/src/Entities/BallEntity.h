#pragma once

#include <algorithm>
#include <functional>

#include "Core/Component/RigidBodyComponent.h"
#include "Core/Component/SpriteComponent.h"
#include "Core/Component/TransformComponent.h"

inline auto ballCollisionCallback = [](Entity self, Entity other) {
    // TODO: bounce sfx sound
};

inline Vec2 CreateRandomBallVelocity(const float ballSpeed) {
    // Keep the reset logic in one place so score handling and initial spawn
    // always produce the same kind of serve speed and direction.
    float velX;
    if (rand() % 2 == 0)
        velX = -ballSpeed;
    else
        velX = ballSpeed;

    const auto factor = static_cast<float>(rand() % std::max(1, static_cast<int>(ballSpeed)) + 1);
    const float velY = (rand() % 2 == 0 ? -factor : factor);
    return Vec2(velX, velY);
}

inline void CenterBallEntity(const Entity entity) {
    auto &transformComponent = Core::GetCoordinator().GetComponent<TransformComponent>(entity);
    const int ballWidth = GetBallWidth();
    const int ballHeight = GetBallHeight();
    const float gameWidth = static_cast<float>(GetGameWidth());
    const float gameHeight = static_cast<float>(GetGameHeight());

    transformComponent.position = Vec2(
        gameWidth / 2.0f - static_cast<float>(ballWidth) / 2.0f,
        gameHeight / 2.0f - static_cast<float>(ballHeight) / 2.0f);
}

inline void StopBallEntity(const Entity entity) {
    auto &rigidBodyComponent = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entity);
    rigidBodyComponent.velocity = Vec2(0.0f, 0.0f);
    rigidBodyComponent.acceleration = Vec2(0.0f, 0.0f);
}

inline void ResetBallEntity(const Entity entity) {
    // Splitting spawn position from serve velocity keeps round transitions
    // explicit: normal scores can re-serve, while match-over can freeze the
    // ball at center without duplicating placement math.
    auto &rigidBodyComponent = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entity);
    CenterBallEntity(entity);
    rigidBodyComponent.velocity = CreateRandomBallVelocity(GetBallSpeed());
    rigidBodyComponent.acceleration = Vec2(0.0f, 0.0f);
}

inline Entity CreateBallEntity(const std::string &entity_name, const std::string &scene_name) {
    const int ballWidth = GetBallWidth();
    const int ballHeight = GetBallHeight();
    const float ballSpeed = GetBallSpeed();
    const float gameWidth = static_cast<float>(GetGameWidth());
    const float gameHeight = static_cast<float>(GetGameHeight());
    SDL_Texture *texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);

    const auto velocity = CreateRandomBallVelocity(ballSpeed);

    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);

    Core::GetCoordinator().AddComponent(
        entity,
        TransformComponent{
            Vec2(gameWidth / 2.0f - static_cast<float>(ballWidth) / 2.0f,
                 gameHeight / 2.0f - static_cast<float>(ballHeight) / 2.0f)
        });
    Core::GetCoordinator().AddComponent(
        entity,
        SpriteComponent{
            texture, // Texture
            {
                // Source rectangle
                42, // X
                5, // Y
                DEFAULT_BALL_WIDTH, // W
                DEFAULT_BALL_HEIGHT // H
            },
            {
                // Destination rectangle
                0, // X
                0, // Y
                static_cast<float>(ballWidth), // W
                static_cast<float>(ballHeight) // H
            },
            SDL_FLIP_NONE, // Flip
            VAUS_SPRITE_FILEPATH
        });
    Core::GetCoordinator().AddComponent(
        entity,
        RigidBodyComponent{
            {0, 0, static_cast<float>(ballWidth), static_cast<float>(ballHeight)}, // Collider
            velocity,
            Vec2(0, 0), // Acceleration
            1.0f, // Mass
            false, // Static?
            false, // Use gravity?
            ballCollisionCallback
        });

    return entity;
}
