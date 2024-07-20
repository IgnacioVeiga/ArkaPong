#pragma once

#include "../Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"
#include "../GameConstants.h"

extern Coordinator gCoordinator;

class MovementSystem : public System
{
public:
    void Init() {}

    void Update(float deltaTime)
    {
        for (auto const &entity : mEntities)
        {
            auto &positionComponent = gCoordinator.GetComponent<PositionComponent>(entity);
            auto &velocityComponent = gCoordinator.GetComponent<VelocityComponent>(entity);
            
            positionComponent.x += velocityComponent.x * deltaTime;
            positionComponent.y += velocityComponent.y * deltaTime;
        }
    }
};
