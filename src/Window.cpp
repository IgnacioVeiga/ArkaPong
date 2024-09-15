#include "Window.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

bool Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        return false;
    if (TTF_Init() == -1)
        return false;
    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        return false;

    Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE; // Resizable flag included

    window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (!window)
        return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
        return false;

    SetWindowMode(0, false, false);

    return true;
}

void Window::CleanUp()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

// TODO: fix fullscreen mode in Linux, not working on KDE
void Window::SetWindowMode(int resolutionIndex, bool fullscreen, bool borderless)
{
    if (resolutionIndex < 0 || resolutionIndex >= availableResolutions.size())
    {
        std::cerr << "Invalid resolution index" << std::endl;
        return;
    }

    int width = availableResolutions[resolutionIndex].width;
    int height = availableResolutions[resolutionIndex].height;

    SDL_SetWindowSize(window, width, height);

    if (fullscreen)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    else if (borderless)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else
    {
        // Normal window mode
        SDL_SetWindowFullscreen(window, 0); // Fullscrenn disabled
    }
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
