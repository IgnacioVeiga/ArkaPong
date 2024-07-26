#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/RenderComponent.h"
#include "../Component/PositionComponent.h"
#include "../../Utils/GameConstants.h"

class RenderSystem : public System
{
public:
    void Init()
    {
        Signature signature;
        signature.set(Game::coordinator.GetComponentType<RenderComponent>());
        Game::coordinator.SetSystemSignature<RenderSystem>(signature);
    }

    void Update()
    {
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::renderer);

        for (auto const &entity : mEntities)
        {
            auto &renderComponent = Game::coordinator.GetComponent<RenderComponent>(entity);
            auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

            SDL_FRect destRect = {
                positionComponent.x,        // X
                positionComponent.y,        // Y
                renderComponent.destRect.w, // W
                renderComponent.destRect.h  // H
            };

            SDL_RenderCopyExF(
                Game::renderer,           // Renderer
                renderComponent.texture,  // Texture
                &renderComponent.srcRect, // Source rectangle
                &destRect,                // Destination rectangle
                0.0,                      // Angle
                nullptr,                  // Center
                renderComponent.flip      // Flip
            );
        }

        SDL_RenderPresent(Game::renderer);
    }
};