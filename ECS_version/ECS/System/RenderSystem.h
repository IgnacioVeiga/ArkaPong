#pragma once

#include <SDL2/SDL.h>
#include "../Coordinator.h"
#include "../Component/RenderComponent.h"
#include "../GameConstants.h"

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
            SDL_RenderCopyEx(Game::renderer, renderComponent.texture, &renderComponent.srcRect, &renderComponent.destRect, 0.0, nullptr, renderComponent.flip);
        }

        SDL_RenderPresent(Game::renderer);
    }
};