#pragma once

#include <SDL2/SDL.h>
#include "Scenes/SceneManager.h"
#include "Window.h"

class Game
{
public:
    bool Init();
    void Run();
    void CleanUp();

    static Window window;
    static Coordinator coordinator;
    static SceneManager *sceneManager;
    static bool game_on;
};
