#pragma once

#include "System.h"
#include "../../ArkaPong/Utils/GameConstants.h"

class MovementSystem : public System
{
public:
	void Init()
	{
		Signature signature{};
		signature.set(Game::coordinator.GetComponentType<TransformComponent>());
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
		auto &transformComponent = Game::coordinator.GetComponent<TransformComponent>(entity);
		auto &velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(entity);

		transformComponent.position.x += velocityComponent.x * deltaTime;
		transformComponent.position.y += velocityComponent.y * deltaTime;
	}

	void CheckOutOfBounds(Entity entity)
	{
		auto &transformComponent = Game::coordinator.GetComponent<TransformComponent>(entity);
		auto &velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(entity);

		// TODO: Define what should happen via a callback, for now this has the behavior of the ball.
		if (transformComponent.position.x > SCREEN_WIDTH || transformComponent.position.x < 0)
		{
			ResetEntityPositionAndVelocity(transformComponent, velocityComponent);
		}

		if (transformComponent.position.y > SCREEN_HEIGHT || transformComponent.position.y < 0)
		{
			velocityComponent.y = -velocityComponent.y;
		}
	}

	void ResetEntityPositionAndVelocity(TransformComponent &transformComponent, VelocityComponent &velocityComponent)
	{
		transformComponent.position = Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		velocityComponent.x = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
		int factor = rand() % BALL_SPEED + 1;
		velocityComponent.y = (rand() % 2 == 0 ? -factor : factor);
	}
};
