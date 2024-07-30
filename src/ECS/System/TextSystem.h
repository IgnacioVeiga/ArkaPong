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

            if (textComponent.dirty)
            {
                UpdateTexture(textComponent);
                textComponent.dirty = false;
            }

            if (textComponent.texture)
            {
                SDL_Rect renderRect = GetAlignedRect(textComponent);
                SDL_RenderCopy(
                    Game::renderer,        // Renderer
                    textComponent.texture, // Texture
                    NULL,                  // Source rectangle
                    &renderRect            // Destination Rectangle
                );
            }
        }
    }

private:
    void UpdateTexture(TextComponent &textComponent)
    {
        if (textComponent.texture)
        {
            SDL_DestroyTexture(textComponent.texture);
        }

        SDL_Surface *surface = TTF_RenderText_Solid(
            textComponent.font,         // Font
            textComponent.text.c_str(), // Text
            textComponent.color         // Color
        );

        if (!surface)
        {
            std::cerr << "Error creating text surface: " << TTF_GetError() << std::endl;
            textComponent.texture = nullptr;
            return;
        }

        textComponent.texture = SDL_CreateTextureFromSurface(Game::renderer, surface);

        if (!textComponent.texture)
        {
            std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
        }

        SDL_FreeSurface(surface);
    }

    SDL_Rect GetAlignedRect(const TextComponent &textComponent)
    {
        SDL_Rect renderRect;
        renderRect.w = 0;
        renderRect.h = 0;
        SDL_QueryTexture(textComponent.texture, NULL, NULL, &renderRect.w, &renderRect.h);

        renderRect.x = textComponent.x;
        renderRect.y = textComponent.y;

        switch (textComponent.alignment)
        {
        case TextAlignment::CENTER:
            renderRect.x -= renderRect.w / 2;
            break;
        case TextAlignment::RIGHT:
            renderRect.x -= renderRect.w;
            break;
        case TextAlignment::LEFT:
        default:
            break;
        }
        return renderRect;
    }
};
