#pragma once

#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/TextComponent.h"

extern Coordinator gCoordinator;

class TextSystem : public System
{
public:
    void Init() {}

    void Update()
    {
        for (auto const &entity : mEntities)
        {
            auto &textComponent = gCoordinator.GetComponent<TextComponent>(entity);
            
            SDL_Surface* surface = TTF_RenderText_Solid(textComponent.font, textComponent.text.c_str(), textComponent.color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

            SDL_RenderCopy(Game::renderer, texture, NULL, &textComponent.destRect);

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
};
