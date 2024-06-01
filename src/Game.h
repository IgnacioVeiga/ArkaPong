#ifndef GAME_H
#define GAME_H

#include "managers/FlowManager.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    static SDL_Renderer *renderer;
    static FlowManager *flowManager;
    static bool game_on;

private:
    static SDL_Window *window;
};

#endif
