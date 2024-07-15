#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Game.h"
#include "utilities/GameConstants.h"
#include "scenes/MenuScene.h"

SDL_Renderer *Game::renderer = nullptr;
SceneManager *Game::sceneManager = nullptr;
SDL_Window *Game::window = nullptr;
bool Game::game_on = true;

int Game::Init_SDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
    {
        SDL_Log("SDL2 initialization failed: %s", SDL_GetError());
        return -1;
    }

    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        SDL_Log("SDL2_mixer initialization failed: %s", Mix_GetError());
        return -1;
    }

    if (TTF_Init() == -1)
    {
        SDL_Log("SDL2_ttf initialization failed: %s", TTF_GetError());
        return -1;
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
        return -1;
    }

    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return -1;
    }

    return 0;
}

void Game::Run()
{
    Game::sceneManager = new SceneManager(
        new MenuScene()
    );

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    SDL_Event event;
    while (Game::game_on)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                Game::game_on = false;
            }
        }

        Game::sceneManager->handleInput();
        Game::sceneManager->update();
        Game::sceneManager->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}

void Game::CleanUp()
{
    if (Game::sceneManager)
    {
        delete Game::sceneManager;
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