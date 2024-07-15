#pragma once
#include "SDL.h"

class Game
{
public:
    bool Init();
    void Run();
    void CleanUp();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};
