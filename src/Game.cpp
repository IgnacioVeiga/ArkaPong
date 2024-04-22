#include "Game.h"
#include "MenuState.h"
#include "GameConstants.h"
#include <SDL2/SDL_mixer.h>
#include <time.h>

Game::Game() : window(nullptr), renderer(nullptr), flowManager(nullptr), isRunning(false)
{
    srand(time(nullptr));

    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return;
    }

    // Inicializar SDL_mixer
    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        // Manejar el error si la inicialización de SDL_mixer falla
        SDL_Log("SDL_mixer initialization failed: %s", Mix_GetError());
        return;
    }

    // Inicializa SDL_ttf
    if (TTF_Init() == -1)
    {
        SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
        SDL_Quit();
        return;
    }

    // Crea la ventana y el renderizador
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

    if (!window || !renderer)
    {
        SDL_Log("Failed to create window or renderer: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return;
    }

    // Configura el flujo de manejo del juego
    flowManager = new GameFlowManager();
    flowManager->changeState(new MenuState(renderer, flowManager));
    isRunning = true;
}

Game::~Game()
{
    if (flowManager)
    {
        delete flowManager;
    }
    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
    }
    if (window)
    {
        SDL_DestroyWindow(window);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void Game::run()
{
    SDL_Event event;
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                isRunning = false;
            }
        }

        flowManager->handleInput();
        flowManager->update();

        SDL_RenderClear(renderer);
        flowManager->render(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(1000 / 60); // 60 FPS
    }
}
