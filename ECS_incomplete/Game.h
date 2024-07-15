#pragma once

class Game
{
public:
    bool Init_SDL();
    void Run();
    void CleanUp();

    static SDL_Renderer* renderer;
    static SceneManager* sceneManager;
    static bool game_on;

private:
    static SDL_Window* window;
};
