#pragma once

#include <iostream>
#include "../ECS/Coordinator.h"

void TriggerAction(Entity entity) {
	std::cout << "Event triggered for entity: " << entity << std::endl;
}

void CheckOutOfBounds(Entity entity) {
	auto& positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);
	auto& velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(entity);

	if (positionComponent.x > SCREEN_WIDTH || positionComponent.x < 0)
	{
		// Center
		positionComponent.x = SCREEN_WIDTH / 2;
		positionComponent.y = SCREEN_HEIGHT / 2;

		// Repeated code (BallEntity.h)
		velocityComponent.x = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
		// vel Y is not always the same
		int factor = rand() % BALL_SPEED + 1;
		// Up or down (random)
		velocityComponent.y = (rand() % 2 == 0 ? -factor : factor);
	}

	if (positionComponent.y > SCREEN_HEIGHT || positionComponent.y < 0)
	{
		// Bounce
		velocityComponent.y = -velocityComponent.y;
	}
}
