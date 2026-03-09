#pragma once

#include <SDL2/SDL_render.h>
#include <string>

struct SpriteComponent {
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_FRect destRect;
    SDL_RendererFlip flip;
    std::string texturePath;
};
