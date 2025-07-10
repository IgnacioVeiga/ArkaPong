#pragma once

#include <SDL2/SDL_render.h>

struct ParallaxLayer {
    SDL_Texture *layerTexture;
    float scrollSpeed;
};
