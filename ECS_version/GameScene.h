#pragma once

#include <SDL2/SDL.h>
#include "Game.h"
#include "Scene.h"
#include "ECS/SystemManager.h"
#include "ECS/Coordinator.h"
#include "ECS/MovementSystem.h"

class GameScene : public Scene
{
public:
    void Init() override
    {
        Entity ball = gCoordinator.CreateEntity();
        Entity playerLeft = gCoordinator.CreateEntity();
        Entity playerRight = gCoordinator.CreateEntity();

        gCoordinator.AddComponent(
            ball,
            PositionComponent{
                .x = SCREEN_WIDTH / 2,
                .y = SCREEN_HEIGHT / 2});

        gCoordinator.AddComponent(
            playerLeft,
            PositionComponent{
                .x = PADDLE_OFFSET,
                .y = SCREEN_HEIGHT / 2});

        gCoordinator.AddComponent(
            playerRight,
            PositionComponent{
                .x = SCREEN_WIDTH - PADDLE_OFFSET,
                .y = SCREEN_HEIGHT / 2});
    };

    void Update() override
    {
        // TODO: update scene logic
    };
};
