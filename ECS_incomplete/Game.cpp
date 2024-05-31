#include "Game.h"
#include "GameConstants.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <time.h>

SDL_Renderer *Game::renderer = nullptr;
SDL_Window *Game::window = nullptr;
bool Game::game_on = true;

Game::Game()
{
    srand(time(NULL));
    initSDL();
    initECS();
}

Game::~Game()
{
    cleanUp();
}

void Game::initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        SDL_Log("SDL2 initialization failed: %s", SDL_GetError());
        game_on = false;
        return;
    }

    window = SDL_CreateWindow(
        GAME_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        game_on = false;
        return;
    }

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        game_on = false;
        return;
    }

    if (TTF_Init() != 0)
    {
        SDL_Log("SDL2_ttf initialization failed: %s", TTF_GetError());
        game_on = false;
        return;
    }

    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_Log("SDL2_mixer initialization failed: %s", Mix_GetError());
        game_on = false;
        return;
    }
}

void Game::initECS()
{
    PositionComponent ballPosition = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    SDL_Surface *surface = SDL_LoadBMP("assets/sprites/ball.bmp");
    if (!surface)
    {
        SDL_Log("Loading texture failed");
        game_on = false;
        return;
    }
    SDL_Texture *ballTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    RenderComponent ballRender = {ballTexture, {
                                                   SCREEN_WIDTH / 2 - BALL_SIZE / 2,  // X
                                                   SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // Y
                                                   BALL_SIZE,                         // W
                                                   BALL_SIZE                          // H
                                               }};
    entities.push_back(std::make_pair(ballPosition, ballRender));
}

void Game::cleanUp()
{
    for (auto &entity : entities)
    {
        SDL_DestroyTexture(entity.second.texture);
    }
    entities.clear();

    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void Game::run() {
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    while (game_on) {
        Uint32 frameStart = SDL_GetTicks();

        // events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                game_on = false;
            }
        }

        // update logic
        for (auto& entity : entities) {
            // example of simple ball movement
            entity.first.x += 1.0f;
            entity.first.y += 1.0f;
        }

        // render
        SDL_RenderClear(renderer);
        for (auto& entity : entities) {
            SDL_Rect dest = entity.second.rect;
            dest.x = static_cast<int>(entity.first.x);
            dest.y = static_cast<int>(entity.first.y);
            SDL_RenderCopy(renderer, entity.second.texture, nullptr, &dest);
        }
        SDL_RenderPresent(renderer);

        // frametime control
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
