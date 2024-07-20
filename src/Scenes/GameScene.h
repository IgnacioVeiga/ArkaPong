#pragma once

#include <SDL2/SDL.h>
#include "Scene.h"
#include "../Game.h"
#include "../ECS/System/SystemManager.h"
#include "../ECS/Coordinator.h"
#include "../ECS/System/MovementSystem.h"
#include "../ECS/System/RenderSystem.h"
#include "../ECS/System/AudioSystem.h"
#include "../ECS/System/TextSystem.h"

class GameScene : public Scene
{
public:
    GameScene(Coordinator *coordinator) : coordinator(coordinator) {}

    void Init() override
    {
        coordinator->RegisterComponent<PositionComponent>();
        coordinator->RegisterComponent<VelocityComponent>();
        coordinator->RegisterComponent<RenderComponent>();
        coordinator->RegisterComponent<AudioComponent>();
        coordinator->RegisterComponent<TextComponent>();

        auto movementSystem = coordinator->RegisterSystem<MovementSystem>();
        {
            Signature signature;
            signature.set(coordinator->GetComponentType<PositionComponent>());
            coordinator->SetSystemSignature<MovementSystem>(signature);
        }
        movementSystem->Init();

        auto renderSystem = coordinator->RegisterSystem<RenderSystem>();
        {
            Signature signature;
            signature.set(coordinator->GetComponentType<RenderComponent>());
            coordinator->SetSystemSignature<RenderSystem>(signature);
        }
        renderSystem->Init();

        auto audioSystem = coordinator->RegisterSystem<AudioSystem>();
        {
            Signature signature;
            signature.set(coordinator->GetComponentType<AudioComponent>());
            coordinator->SetSystemSignature<AudioSystem>(signature);
        }
        audioSystem->Init();

        auto textSystem = coordinator->RegisterSystem<TextSystem>();
        {
            Signature signature;
            signature.set(coordinator->GetComponentType<TextComponent>());
            coordinator->SetSystemSignature<TextSystem>(signature);
        }
        textSystem->Init();

        // TODO: replace for a method like TextureManager
        SDL_Surface *tempSurface = SDL_LoadBMP("assets/sprites/vaus.bmp");
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        SDL_FreeSurface(tempSurface);

        Entity ball = coordinator->CreateEntity();
        coordinator->AddComponent(
            ball,
            PositionComponent{
                .x = SCREEN_WIDTH / 2,
                .y = SCREEN_HEIGHT / 2});
        coordinator->AddComponent(
            ball,
            VelocityComponent{BALL_SPEED, BALL_SPEED});
        coordinator->AddComponent(
            ball,
            RenderComponent{
                texture,
                {42, 5, BALL_SIZE, BALL_SIZE},
                {SCREEN_WIDTH / 2 - BALL_SIZE / 2, SCREEN_HEIGHT / 2 - BALL_SIZE / 2, BALL_SIZE, BALL_SIZE},
                SDL_FLIP_NONE});

        SDL_Rect srcRectPaddle = {0, 0, PADDLE_WIDTH, PADDLE_HEIGHT};
        Entity playerLeft = coordinator->CreateEntity();
        coordinator->AddComponent(
            playerLeft,
            PositionComponent{
                .x = PADDLE_OFFSET,
                .y = SCREEN_HEIGHT / 2});
        coordinator->AddComponent(
            playerLeft,
            VelocityComponent{PADDLE_SPEED, PADDLE_SPEED});
        coordinator->AddComponent(
            playerLeft,
            RenderComponent{
                texture,
                srcRectPaddle,
                {PADDLE_OFFSET, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT},
                SDL_FLIP_NONE});

        Entity playerRight = coordinator->CreateEntity();
        coordinator->AddComponent(
            playerRight,
            PositionComponent{
                .x = SCREEN_WIDTH - PADDLE_OFFSET,
                .y = SCREEN_HEIGHT / 2});
        coordinator->AddComponent(
            playerRight,
            VelocityComponent{PADDLE_SPEED, PADDLE_SPEED});
        coordinator->AddComponent(
            playerRight,
            RenderComponent{
                texture,
                srcRectPaddle,
                {SCREEN_WIDTH - PADDLE_OFFSET, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, PADDLE_WIDTH, PADDLE_HEIGHT},
                SDL_FLIP_HORIZONTAL});
    };

    void Update(float deltaTime) override
    {
        coordinator->GetSystem<MovementSystem>()->Update(deltaTime);
        coordinator->GetSystem<RenderSystem>()->Update();
        coordinator->GetSystem<AudioSystem>()->Update();
        coordinator->GetSystem<TextSystem>()->Update();
    };

private:
    Coordinator *coordinator;
};
