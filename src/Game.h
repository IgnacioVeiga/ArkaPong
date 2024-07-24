#pragma once

#include <SDL2/SDL.h>
#include "Scenes/SceneManager.h"

class Game
{
public:
    bool Init_SDL();
    void Init_ECS();
    void Run();
    void CleanUp();

    static SDL_Renderer *renderer;
    static Coordinator coordinator;
    static SceneManager *sceneManager;
    static bool game_on;

private:
    static SDL_Window *window;
};
