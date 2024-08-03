#pragma once

#include "../Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/InputComponent.h"
#include "../../Utils/GameConstants.h"
#include "../../Utils/Events.h"

class MovementSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<PositionComponent>());
		signature.set(Game::coordinator.GetComponentType<VelocityComponent>());
		Game::coordinator.SetSystemSignature<MovementSystem>(signature);
	}

	void Update(float deltaTime)
	{
		for (auto const& entity : mEntities)
		{
			auto& positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);
			auto& velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(entity);

			if (Game::coordinator.HasComponent<InputComponent>(entity))
			{
				auto& inputComponent = Game::coordinator.GetComponent<InputComponent>(entity);

				if (inputComponent.keyStates[inputComponent.keyMappings["up"]])
				{
					/*positionComponent.y -= velocityComponent.y * deltaTime;*/
					positionComponent.y = std::max(0, static_cast<int>(positionComponent.y - velocityComponent.y * deltaTime));
				}
				if (inputComponent.keyStates[inputComponent.keyMappings["down"]])
				{
					/*positionComponent.y += velocityComponent.y * deltaTime;*/
					positionComponent.y = std::min(static_cast<int>(SCREEN_HEIGHT - PADDLE_HEIGHT), static_cast<int>(positionComponent.y + velocityComponent.y * deltaTime));
				}

				continue;
			}

			// No-gravity movement
			positionComponent.x += velocityComponent.x * deltaTime;
			positionComponent.y += velocityComponent.y * deltaTime;

			CheckOutOfBounds(entity);
		}
	}
};
