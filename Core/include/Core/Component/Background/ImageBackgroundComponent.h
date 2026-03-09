#pragma once

#include <SDL2/SDL_render.h>
#include <string>

struct ImageBackgroundComponent {
    SDL_Texture *imageTexture;
    int width;
    int height;
    std::string texturePath;
};
