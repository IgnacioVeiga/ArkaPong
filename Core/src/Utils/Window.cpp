#include "Core/Utils/Window.h"
#include "Core/Utils/CoreConstants.h"

#include <SDL2/SDL.h>

#if defined(_MSC_VER)
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <iostream>

Window::Window()
    : window(nullptr), renderer(nullptr),
      availableResolutions{
          {SCREEN_WIDTH, SCREEN_HEIGHT},
          {1280, 720},
          {1920, 1080},
          {2560, 1440},
          {3840, 2160}
      }
{
}

Window::~Window() {
    CleanUp();
}

bool Window::Init(const char* title) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    if (TTF_Init() == -1) {
        SDL_Log("TTF_Init failed: %s", TTF_GetError());
        return false;
    }

    if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
        return false;
    }

    constexpr Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (!window) {
        SDL_Log("Window creation failed: %s", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_Log("Renderer creation failed: %s", SDL_GetError());
        return false;
    }

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return true;
}

void Window::CleanUp() const {
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    Mix_CloseAudio();
    TTF_Quit();
    SDL_Quit();
}

// TODO: fix fullscreen mode in Linux, not working on KDE
void Window::SetWindowMode(const int resolutionIndex, const Uint32 flags) const {
    if (resolutionIndex < 0 || resolutionIndex >= static_cast<int>(availableResolutions.size())) {
        std::cerr << "Invalid resolution index" << std::endl;
        return;
    }

    const auto& res = availableResolutions[resolutionIndex];

    SDL_SetWindowSize(window, res.width, res.height);
    SDL_SetWindowFullscreen(window, flags);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    //#ifdef __linux__
    //  SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    //#endif
}
