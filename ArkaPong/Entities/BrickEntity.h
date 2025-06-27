#pragma once

#include <functional>
#include "../Utils/GameEnums.h"
#include "../Utils/BrickUtils.h"

inline auto brickCollisionCallback = [](const Entity self, Entity other) {
    Core::coordinator.MarkEntityForDeletion(self);
};

inline void CreateBrickEntity(const std::string &entity_name, const std::string &scene_name, Vec2 pos, int brickType) {
    SDL_Texture *texture = TextureManager::LoadTexture(BRICKS_SPRITE_FILEPATH);

    const auto type = static_cast<BrickType>(brickType);
    const SDL_Rect srcRect = GetBrickSrcRect(type);

    const Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);

    Core::coordinator.AddComponent(
        entity,
        TransformComponent{pos});
    Core::coordinator.AddComponent(
        entity,
        SpriteComponent{
            texture, // Texture
            srcRect,
            {
                // Destination rectangle
                0, // X
                0, // Y
                BRICK_WIDTH, // W
                BRICK_HEIGHT // H
            },
            SDL_FLIP_NONE // Flip
        });
    Core::coordinator.AddComponent(
        entity,
        RigidBodyComponent{
            {0, 0, BRICK_WIDTH, BRICK_HEIGHT}, // Collider
            Vec2(0, 0), // Velocity
            Vec2(0, 0), // Acceleration
            1.0f, // Mass
            true, // Static?
            false, // Use gravity?
            brickCollisionCallback
        });
}
