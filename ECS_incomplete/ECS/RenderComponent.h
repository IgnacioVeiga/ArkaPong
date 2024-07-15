#pragma once
#include <SDL2/SDL.h>

struct RenderComponent
{
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
};