#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "Ball.h"
#include "Paddle.h"
#include "GameConstants.h"
#include "AudioManager.h"

int main(int argc, char *args[])
{
    // Inicialización de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    // Inicializa SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    if (!loadMedia())
    {
        printf("Failed to load media!\n");
        return -1;
    }

    // Creación de la ventana
    SDL_Window *window = SDL_CreateWindow("Pong Game",
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window)
    {
        SDL_Log("Ventana no pudo ser creada: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Creación del renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        SDL_Log("Renderer no pudo ser creado: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Creación de objetos del juego
    Ball ball(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 - 10);
    Paddle leftPaddle(30, SCREEN_HEIGHT / 2 - 50);
    Paddle rightPaddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2 - 50);

    // Estado del teclado
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    // Bucle principal del juego
    bool running = true;
    SDL_Event e;
    while (running)
    {
        // Procesamiento de eventos
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        // Movimiento basado en el estado del teclado
        if (state[SDL_SCANCODE_UP])
            rightPaddle.moveUp();
        if (state[SDL_SCANCODE_DOWN])
            rightPaddle.moveDown();

        if (state[SDL_SCANCODE_W])
            leftPaddle.moveUp();
        if (state[SDL_SCANCODE_S])
            leftPaddle.moveDown();

        // Mover la pelota
        ball.move();

        // Detectar colisiones
        ball.detectCollision(leftPaddle);
        ball.detectCollision(rightPaddle);

        // Renderizar
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
        SDL_RenderClear(renderer);

        ball.render(renderer);
        leftPaddle.render(renderer);
        rightPaddle.render(renderer);

        SDL_RenderPresent(renderer);

        // 60 FPS
        SDL_Delay(1000 / 60);
    }

    // Limpieza
    closeAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
