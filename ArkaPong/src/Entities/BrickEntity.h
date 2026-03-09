#pragma once

#include <functional>
#include "../Components/BrickComponent.h"
#include "../Utils/GameEnums.h"
#include "../Utils/BrickUtils.h"
#include "Core/Component/RigidBodyComponent.h"
#include "Core/Component/SpriteComponent.h"
#include "Core/Component/TransformComponent.h"

inline auto brickCollisionCallback = [](const Entity self, Entity other) {
    Core::GetCoordinator().MarkEntityForDeletion(self);
};

inline void CreateBrickEntity(const std::string &entity_name, const std::string &scene_name, const Vec2 pos, int brickType) {
    const int brickWidth = GetBrickWidth();
    const int brickHeight = GetBrickHeight();
    SDL_Texture *texture = TextureManager::LoadTexture(BRICKS_SPRITE_FILEPATH);

    const auto type = static_cast<BrickType>(brickType);
    const SDL_Rect srcRect = GetBrickSrcRect(type);
    const bool clearsLevel = DoesBrickCountForLevelClear(type);

    const Entity entity = Core::GetCoordinator().CreateEntity(
        entity_name,
        scene_name,
        "Brick",
        clearsLevel ? "Objective" : "Decorative");

    Core::GetCoordinator().AddComponent(
        entity,
        TransformComponent{pos});
    Core::GetCoordinator().AddComponent(
        entity,
        SpriteComponent{
            texture, // Texture
            srcRect,
            {
                // Destination rectangle
                0, // X
                0, // Y
                static_cast<float>(brickWidth), // W
                static_cast<float>(brickHeight) // H
            },
            SDL_FLIP_NONE, // Flip
            BRICKS_SPRITE_FILEPATH
        });
    Core::GetCoordinator().AddComponent(
        entity,
        RigidBodyComponent{
            {0, 0, static_cast<float>(brickWidth), static_cast<float>(brickHeight)}, // Collider
            Vec2(0, 0), // Velocity
            Vec2(0, 0), // Acceleration
            1.0f, // Mass
            true, // Static?
            false, // Use gravity?
            brickCollisionCallback
        });
    Core::GetCoordinator().AddComponent(
        entity,
        BrickComponent{
            type,
            clearsLevel
        });
}
