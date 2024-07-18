#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Game.h"
#include "GameScene.h"
#include "GameConstants.h"
#include "SceneManager.h"

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
void Game::Run()
{
    sceneManager = new SceneManager();
    sceneManager->AddScene("GameScene", std::make_unique<GameScene>());
    sceneManager->LoadScene("GameScene");

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

        sceneManager->Update(1.0f / 60.0f);
        sceneManager->Render(renderer);

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