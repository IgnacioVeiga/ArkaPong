#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../../Utils/TextureManager.h"
#include "../Component/AnimationComponent.h"
#include "../Component/SpriteComponent.h"

Entity CreateAnimatedEntity(const std::string &texturePath, int frameCount, int frameWidth, int frameHeight, int animationSpeed, bool loop, float posX, float posY)
{
    Entity entity = Game::coordinator.CreateEntity();

    SDL_Texture *texture = TextureManager::LoadTexture(texturePath.c_str());
    Game::coordinator.AddComponent(
        entity,
        PositionComponent{
            posX, // X
            posY  // Y
        });
    Game::coordinator.AddComponent(
        entity,
        VelocityComponent{
            0, // X
            0  // Y
        });
    Game::coordinator.AddComponent(
        entity,
        SpriteComponent{
            texture,
            {0, 0, frameWidth, frameHeight}, // Source rectangle
            {0, 0, static_cast<float>(frameWidth), static_cast<float>(frameHeight)},
            SDL_FLIP_NONE});

    Game::coordinator.AddComponent(
        entity,
        AnimationComponent{
            0,              // currentFrame
            frameCount,     // frameCount
            frameWidth,     // frameWidth
            frameHeight,    // frameHeight
            animationSpeed, // animationSpeed
            0,              // elapsedTime
            loop,           // loop
            true            // isPlaying
        });

    return entity;
}
