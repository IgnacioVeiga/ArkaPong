#include "Game.h"
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "GameConstants.h"

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
    Entity playerLeft = entityManager.createEntity();
    componentManager.addComponent(playerLeft.getId(), PositionComponent{50, SCREEN_HEIGHT / 2});
    componentManager.addComponent(playerLeft.getId(), VelocityComponent{0, 0});
    componentManager.addComponent(playerLeft.getId(), MovementComponent{PADDLE_SPEED});
    componentManager.addComponent(playerLeft.getId(), InputComponent{SDL_SCANCODE_W, SDL_SCANCODE_S});
    SDL_Texture *textureLeft;
    textureLeft = renderSystem.LoadTexture("assets/sprites/paddle.bmp");
    SDL_Rect rectLeft = {
        PADDLE_OFFSET,                         // X
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, // Y
        PADDLE_WIDTH,                          // W
        PADDLE_HEIGHT                          // H
    };
    componentManager.addComponent(playerLeft.getId(), RenderComponent{textureLeft, rectLeft});

    Entity playerRight = entityManager.createEntity();
    componentManager.addComponent(playerRight.getId(), PositionComponent{SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2});
    componentManager.addComponent(playerRight.getId(), VelocityComponent{0, 0});
    componentManager.addComponent(playerRight.getId(), MovementComponent{PADDLE_SPEED});
    componentManager.addComponent(playerRight.getId(), InputComponent{SDL_SCANCODE_UP, SDL_SCANCODE_DOWN});
    SDL_Texture *textureRight;
    textureRight = renderSystem.LoadTexture("assets/sprites/paddle.bmp");
    SDL_Rect rectRight = {
        SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH, // X
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2,       // Y
        PADDLE_WIDTH,                                // W
        PADDLE_HEIGHT                                // H
    };
    componentManager.addComponent(playerLeft.getId(), RenderComponent{textureRight, rectRight});

    inputSystem.addEntity(playerLeft);
    inputSystem.addEntity(playerRight);

    movementSystem.addEntity(playerLeft);
    movementSystem.addEntity(playerRight);
}

void Game::cleanUp()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);

    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

void Game::run()
{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    while (game_on)
    {
        Uint32 frameStart = SDL_GetTicks();

        // events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                game_on = false;
            }
        }

        inputSystem.update(componentManager);
        movementSystem.update(componentManager);
        renderSystem.render(entities);

        // frametime control
        Uint32 frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
}
