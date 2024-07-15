#include "Game.h"
#include "SDL.h"
#include "GameScene.h"
#include "SceneManager.h"

SceneManager sceneManager;

bool Game::Init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("ArkaPong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    // Inicializar la escena
    GameScene* gameScene = new GameScene();
    sceneManager.LoadScene(gameScene);

    return true;
}

void Game::Run() {
    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            // Aquí deberíamos agregar el manejo de eventos de la escena actual
        }

        sceneManager.Update(1.0f / 60.0f); // Actualizamos con un tiempo fijo por ahora
        SDL_RenderClear(renderer);
        sceneManager.Render(renderer);
        SDL_RenderPresent(renderer);
    }
}

void Game::CleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
