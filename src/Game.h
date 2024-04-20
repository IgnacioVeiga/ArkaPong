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

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    GameFlowManager *flowManager; // Gestor del flujo del juego
    bool isRunning;

    void init();     // Inicialización de componentes del juego
    void mainLoop(); // Bucle principal del juego
    void cleanUp();  // Limpieza de recursos
};

#endif
