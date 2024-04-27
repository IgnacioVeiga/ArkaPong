#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "GameFlowManager.h"

class Game
{
public:
    Game();
    ~Game();
    void run(); // Método para iniciar el juego
    static SDL_Renderer *renderer;

private:
    SDL_Window *window;
    GameFlowManager *flowManager; // Gestor del flujo del juego
    bool isRunning;
};

#endif
