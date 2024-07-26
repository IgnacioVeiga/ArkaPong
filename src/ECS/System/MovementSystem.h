#pragma once

#include "../Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/InputComponent.h"
#include "../../Utils/GameConstants.h"

class MovementSystem : public System
{
public:
    void Init()
    {
        Signature signature;
        signature.set(Game::coordinator.GetComponentType<PositionComponent>());
        Game::coordinator.SetSystemSignature<MovementSystem>(signature);
    }

    void Update(float deltaTime)
    {
        for (auto const &entity : mEntities)
        {
            auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);
            auto &velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(entity);

            if (Game::coordinator.HasComponent<InputComponent>(entity))
            {
                auto &inputComponent = Game::coordinator.GetComponent<InputComponent>(entity);

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
