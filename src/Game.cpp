#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <iostream>

#include "Game.h"
#include "Utils/GameConstants.h"
#include "Scenes/SceneManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"
#include "ECS/Coordinator.h"

Coordinator Game::coordinator;
SDL_Renderer *Game::renderer = nullptr;
SceneManager *Game::sceneManager = nullptr;
SDL_Window *Game::window = nullptr;
bool Game::game_on = true;

bool Game::Init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
    {
        SDL_Log("SDL2 initialization failed: %s", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        SDL_Log("SDL2_mixer initialization failed: %s", Mix_GetError());
        return false;
    }

    if (TTF_Init() == -1)
    {
        SDL_Log("SDL2_ttf initialization failed: %s", TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        GAME_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}

void Game::Init_ECS()
{
    coordinator.Init();
    coordinator.RegisterComponent<InputComponent>();
    coordinator.RegisterComponent<PositionComponent>();
    coordinator.RegisterComponent<VelocityComponent>();
    coordinator.RegisterComponent<SpriteComponent>();
    coordinator.RegisterComponent<AudioComponent>();
    coordinator.RegisterComponent<TextComponent>();
    coordinator.RegisterComponent<CollisionComponent>();
    coordinator.RegisterComponent<TileBackgroundComponent>();

    coordinator.RegisterSystem<InputSystem>()->Init();
    coordinator.RegisterSystem<MovementSystem>()->Init();
    coordinator.RegisterSystem<SpriteSystem>()->Init();
    coordinator.RegisterSystem<AudioSystem>()->Init();
    coordinator.RegisterSystem<TextSystem>()->Init();
    coordinator.RegisterSystem<CollisionSystem>()->Init();
    coordinator.RegisterSystem<TileBackgroundSystem>()->Init();
}

void Game::Run()
{
    sceneManager = new SceneManager();
    sceneManager->Add("MainMenu", std::make_unique<MainMenuScene>());
    sceneManager->Add("Game", std::make_unique<GameScene>());
    sceneManager->Init("Game");

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

        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::renderer);

        // TODO: fix this
        // sceneManager->Update(frameTime / 1000.0f);
        sceneManager->Update(1);

        SDL_RenderPresent(Game::renderer);

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
    if (sceneManager)
    {
        delete sceneManager;
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}