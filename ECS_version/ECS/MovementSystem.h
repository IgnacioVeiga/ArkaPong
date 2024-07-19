#pragma once

#include "Coordinator.h"
#include "PositionComponent.h"
#include "../GameConstants.h"

extern Coordinator gCoordinator;

class MovementSystem : public System
{
public:
    void Init() { }

    void Update(float deltaTime)
    {
        for (auto const &entity : mEntities)
        {
            auto &positionComponent = gCoordinator.GetComponent<PositionComponent>(entity);
            // TODO: update position
        }
    }
};
