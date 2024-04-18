#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "GameConstants.h"
#include "GameStateManager.h"

int main(int argc, char *argv[])
{
    char *basePath = SDL_GetBasePath();
    if (basePath)
    {
        printf("Current path is: %s\n", basePath);
        SDL_free(basePath);
    }

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();
    Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);

    SDL_Window *window = SDL_CreateWindow(GAME_TITLE,
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH,
                                          SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1,
                                                SDL_RENDERER_ACCELERATED);
    SDL_Event event;

    GameStateManager gameStateManager(renderer);
    bool gameRunning = true;

    // Para la direccion de la pelota aleatoria
    srand(time(nullptr));

    while (gameRunning)
    {
        // Event handling
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                gameRunning = false;
            }
        }
        gameStateManager.handleInput();

        // Game logic
        gameStateManager.update();

        // Render stuff
        gameStateManager.render(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
