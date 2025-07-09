#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <vector>

struct Resolution {
    int width;
    int height;
};

class Window {
public:
    Window();
    ~Window();

    bool Init(const char* title);
    void CleanUp() const;
    void SetWindowMode(int resolutionIndex, Uint32 flags) const;

    [[nodiscard]] SDL_Window* GetWindow() const { return window; }
    [[nodiscard]] SDL_Renderer* GetRenderer() const { return renderer; }

    std::vector<Resolution> availableResolutions;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};
