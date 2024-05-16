#include "Game.h"
#include "MenuState.h"
#include "GameConstants.h"
#include <SDL2/SDL_mixer.h>
#include <time.h>

SDL_Renderer *Game::renderer = nullptr;
GameFlowManager *Game::gFlowManager = nullptr;
SDL_Window *Game::window = nullptr;

Game::Game()
{
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
    {
        SDL_Log("SDL2 initialization failed: %s", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        SDL_Log("SDL2_mixer initialization failed: %s", Mix_GetError());
        return;
    }

    if (TTF_Init() == -1)
    {
        SDL_Log("SDL2_ttf initialization failed: %s", TTF_GetError());
        return;
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
        return;
    }

    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return;
    }

    Game::gFlowManager = new GameFlowManager();
    Game::gFlowManager->changeState(new MenuState());
}

Game::~Game()
{
    if (Game::gFlowManager)
    {
        delete Game::gFlowManager;
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

void Game::run()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    SDL_Event event;
    while (true)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                // quit game
                return;
            }
        }

        Game::gFlowManager->handleInput();
        Game::gFlowManager->update();
        Game::gFlowManager->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
