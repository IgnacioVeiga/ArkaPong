#pragma once

#include "../Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"
#include "../../Utils/Constants.h"
#include <algorithm>

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
		for (auto const &entity : mEntities)
		{
			if (!Game::coordinator.HasComponent<InputComponent>(entity))
			{
				UpdateEntityMovement(entity, deltaTime);
			}

			CheckOutOfBounds(entity);
		}
	}

private:
	void UpdateEntityMovement(Entity entity, float deltaTime)
	{
		auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);
		auto &velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(entity);

		positionComponent.x += velocityComponent.x * deltaTime;
		positionComponent.y += velocityComponent.y * deltaTime;
	}

	void CheckOutOfBounds(Entity entity)
	{
		auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);
		auto &velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(entity);

		if (positionComponent.x > SCREEN_WIDTH || positionComponent.x < 0)
		{
			ResetEntityPositionAndVelocity(positionComponent, velocityComponent);
		}

		if (positionComponent.y > SCREEN_HEIGHT || positionComponent.y < 0)
		{
			velocityComponent.y = -velocityComponent.y;
		}
	}

	void ResetEntityPositionAndVelocity(PositionComponent &positionComponent, VelocityComponent &velocityComponent)
	{
		positionComponent.x = SCREEN_WIDTH / 2;
		positionComponent.y = SCREEN_HEIGHT / 2;

		velocityComponent.x = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
		int factor = rand() % BALL_SPEED + 1;
		velocityComponent.y = (rand() % 2 == 0 ? -factor : factor);
	}
};
