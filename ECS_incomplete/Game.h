#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <unordered_map>
#include "Components.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    static SDL_Renderer *renderer;
    static bool game_on;

private:
    void initSDL();
    void initECS();
    void cleanUp();
    static SDL_Window *window;
    std::vector<std::pair<PositionComponent, RenderComponent>> entities;
};

#endif
