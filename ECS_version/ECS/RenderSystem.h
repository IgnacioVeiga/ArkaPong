#pragma once

#include <SDL2/SDL.h>
#include "Coordinator.h"
#include "RenderComponent.h"
#include "../GameConstants.h"

extern Coordinator gCoordinator;

class RenderSystem : public System
{
public:
    void Init() {}

    void Update()
    {
        for (auto const &entity : mEntities)
        {
            auto &renderComponent = gCoordinator.GetComponent<RenderComponent>(entity);
            // TODO: render with SDL2
        }
    }
};
