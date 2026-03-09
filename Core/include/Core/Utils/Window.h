#pragma once

#include "Configuration.h"
#include "Core/CoreExport.h"
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <vector>

struct Resolution {
    int width;
    int height;
};

class CORE_API Window {
public:
    Window();
    ~Window();

    bool Init(const char* title, const json& config);
    void CleanUp();
    void SetWindowMode(int resolutionIndex, Uint32 flags);

    [[nodiscard]] SDL_Window* GetWindow() const { return window; }
    [[nodiscard]] SDL_Renderer* GetRenderer() const { return renderer; }
    [[nodiscard]] int GetLogicalWidth() const { return logicalWidth; }
    [[nodiscard]] int GetLogicalHeight() const { return logicalHeight; }
    [[nodiscard]] int GetWindowWidth() const { return windowWidth; }
    [[nodiscard]] int GetWindowHeight() const { return windowHeight; }

    std::vector<Resolution> availableResolutions;

private:
    int logicalWidth;
    int logicalHeight;
    int windowWidth;
    int windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
};
