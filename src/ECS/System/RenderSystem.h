#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/RenderComponent.h"
#include "../Component/PositionComponent.h"
#include "../../GameConstants.h"

extern Coordinator gCoordinator;

class RenderSystem : public System
{
public:
    void Init() {}

    void Update()
    {
        SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        SDL_RenderClear(Game::renderer);

        for (auto const &entity : mEntities)
        {
            auto &renderComponent = gCoordinator.GetComponent<RenderComponent>(entity);
            auto &positionComponent = gCoordinator.GetComponent<PositionComponent>(entity);

            SDL_FRect destRect = {
                positionComponent.x,
                positionComponent.y,
                renderComponent.destRect.w,
                renderComponent.destRect.h};

            SDL_RenderCopyExF(Game::renderer, renderComponent.texture, &renderComponent.srcRect, &destRect, 0.0, nullptr, renderComponent.flip);
        }

        SDL_RenderPresent(Game::renderer);
    }
};