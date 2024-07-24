#pragma once

#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/TextComponent.h"

class TextSystem : public System
{
public:
    void Init()
    {
        Signature signature;
        signature.set(Game::coordinator.GetComponentType<TextComponent>());
        Game::coordinator.SetSystemSignature<TextSystem>(signature);
    }

    void Update()
    {
        for (auto const &entity : mEntities)
        {
            auto &textComponent = Game::coordinator.GetComponent<TextComponent>(entity);

            SDL_Surface *surface = TTF_RenderText_Solid(
                textComponent.font,         // Font filepath
                textComponent.text.c_str(), // Text
                textComponent.color         // Color
            );

            SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

            SDL_RenderCopy(
                Game::renderer,         // Renderer
                texture,                // Texture
                NULL,                   // Source rectange
                &textComponent.destRect // Destination Rectangle
            );

            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    }
};
