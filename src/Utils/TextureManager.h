#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include "../Game.h"

class TextureManager
{
public:
    static SDL_Texture* LoadTexture(const char* path) {
        SDL_Surface* surface = SDL_LoadBMP(path);
        if (!surface) {
            std::cerr << "Error loading BMP: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);

        if (!texture) {
            std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
        }

        return texture;
    }
};
