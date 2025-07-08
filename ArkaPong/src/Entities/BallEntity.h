#pragma once

#include <functional>

inline auto ballCollisionCallback = [](Entity self, Entity other) {
    // TODO: bounce sfx sound
};

inline void CreateBallEntity(const std::string &entity_name, const std::string &scene_name) {
    SDL_Texture *texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);

    // Find another way to get a random velocity direction
    float velX;
    if (rand() % 2 == 0)
        velX = -BALL_SPEED;
    else
        velX = BALL_SPEED;
    // velY is not always the same
    const auto factor = static_cast<float>(rand() % static_cast<int>(BALL_SPEED) + 1);
    // Up or down (random)
    const float velY = (rand() % 2 == 0 ? -factor : factor);
    const auto velocity = Vec2(velX, velY);

    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);

    Core::GetCoordinator().AddComponent(
        entity,
        TransformComponent{
            Vec2(static_cast<float_t>(SCREEN_WIDTH) / 2 - static_cast<float_t>(BALL_SIZE) / 2,
                 static_cast<float_t>(SCREEN_HEIGHT) / 2 - static_cast<float_t>(BALL_SIZE) / 2)
        });
    Core::GetCoordinator().AddComponent(
        entity,
        SpriteComponent{
            texture, // Texture
            {
                // Source rectangle
                42, // X
                5, // Y
                BALL_SIZE, // W
                BALL_SIZE // H
            },
            {
                // Destination rectangle
                0, // X
                0, // Y
                BALL_SIZE, // W
                BALL_SIZE // H
            },
            SDL_FLIP_NONE // Flip
        });
    Core::GetCoordinator().AddComponent(
        entity,
        RigidBodyComponent{
            {0, 0, BALL_SIZE, BALL_SIZE}, // Collider
            velocity,
            Vec2(0, 0), // Acceleration
            1.0f, // Mass
            false, // Static?
            false, // Use gravity?
            ballCollisionCallback
        });
}
