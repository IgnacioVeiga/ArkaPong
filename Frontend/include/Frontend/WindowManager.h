#pragma once

#include <SDL2/SDL.h>
#include <imgui.h>
#include <string>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

namespace Frontend {
    class WindowManager {
    public:
        bool Init(const std::string& configPath);
        void Run();
        private:
        void CleanUp();
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        bool running = true;
    };
}
