#pragma once

#include "../Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/InputComponent.h"
#include "../../GameConstants.h"

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

            if (gCoordinator.HasComponent<InputComponent>(entity))
            {
                auto &inputComponent = gCoordinator.GetComponent<InputComponent>(entity);

                if (inputComponent.keyStates[inputComponent.keyMappings["up"]])
                {
                    positionComponent.y -= velocityComponent.y * deltaTime;
                }
                if (inputComponent.keyStates[inputComponent.keyMappings["down"]])
                {
                    positionComponent.y += velocityComponent.y * deltaTime;
                }
            }
        }
    }
};
