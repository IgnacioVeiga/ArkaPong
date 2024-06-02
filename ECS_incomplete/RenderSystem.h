#pragma once

#include "Components.h"
#include "Game.h"

class RenderSystem
{
public:
    void render(std::vector<std::pair<PositionComponent, RenderComponent>> &entities)
    {
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::renderer);

        for (auto &entity : entities)
        {
            SDL_Rect dest = entity.second.rect;
            dest.x = static_cast<int>(entity.first.x);
            dest.y = static_cast<int>(entity.first.y);
            SDL_RenderCopy(Game::renderer, entity.second.texture, nullptr, &dest);
        }

        SDL_RenderPresent(Game::renderer);
    }

    static SDL_Texture *LoadTexture(const char *filename)
    {
        SDL_Surface *tempSurface = SDL_LoadBMP(filename);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
        SDL_FreeSurface(tempSurface);
        return texture;
    }
};
