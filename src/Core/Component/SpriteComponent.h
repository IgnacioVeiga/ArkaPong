#pragma once

struct SpriteComponent
{
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_FRect destRect;
    SDL_RendererFlip flip;
};
