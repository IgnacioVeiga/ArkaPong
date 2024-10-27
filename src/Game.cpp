#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "Game.h"
#include "Scenes/SceneManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"
#include "ECS/Coordinator.h"

Coordinator Game::coordinator;
Window Game::window;
SceneManager *Game::sceneManager = nullptr;
bool Game::game_on = true;

bool Game::Init()
{
    if (!window.Init())
        return false;

    coordinator.Init();
    coordinator.RegisterComponent<BaseComponent>();
    coordinator.RegisterSystem<BaseSystem>()->Init();
    return true;
}

void Game::Run()
{
    sceneManager = new SceneManager();
    sceneManager->Add("MainMenu", std::make_unique<MainMenuScene>());
    sceneManager->Add("Game", std::make_unique<GameScene>());
    sceneManager->Init("MainMenu");

    const int FPS = 60;
    // target time per frame in milliseconds
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameTime;

    SDL_Event event;
    while (game_on)
    {
        // Frame start time
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game_on = false;
            }
        }

        // The game logic is updated and the frameTime is converted to seconds.
        frameTime = SDL_GetTicks() - frameStart;

        SDL_SetRenderDrawColor(window.GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(window.GetRenderer());

        // TODO: fix this
        // sceneManager->Update(frameTime / 1000.0f);
        sceneManager->Update(1);

        SDL_RenderPresent(window.GetRenderer());

        // SDL_Delay() is used to wait only if the current frame has completed faster than expected.
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            // Wait the necessary time to maintain constant FPS
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game::CleanUp()
{
    window.CleanUp();
}