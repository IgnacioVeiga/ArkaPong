#pragma once

#include <SDL2/SDL_render.h>

struct SpriteComponent
{
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_FRect destRect;
    SDL_RendererFlip flip;
};
