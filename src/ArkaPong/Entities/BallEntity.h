#pragma once

#include <functional>

auto ballCollisionCallback = [](Entity self, Entity other)
{
	auto &velSelf = Game::coordinator.GetComponent<VelocityComponent>(self);
	auto &posSelf = Game::coordinator.GetComponent<TransformComponent>(self);
	auto &colSelf = Game::coordinator.GetComponent<CollisionComponent>(self);

	auto &posOther = Game::coordinator.GetComponent<TransformComponent>(other);
	auto &colOther = Game::coordinator.GetComponent<CollisionComponent>(other);

	// Calculate overlap on each side of the collision
	float overlapLeft = (posSelf.position.x + colSelf.collider.w) - posOther.position.x;
	float overlapRight = (posOther.position.x + colOther.collider.w) - posSelf.position.x;
	float overlapTop = (posSelf.position.y + colSelf.collider.h) - posOther.position.y;
	float overlapBottom = (posOther.position.y + colOther.collider.h) - posSelf.position.y;

	// Determine which side the collision is coming from
	bool fromLeft = fabs(overlapLeft) < fabs(overlapRight);
	bool fromTop = fabs(overlapTop) < fabs(overlapBottom);

	// Find the minimum overlap in the X and Y axes
	float minOverlapX = fromLeft ? overlapLeft : overlapRight;
	float minOverlapY = fromTop ? overlapTop : overlapBottom;

	// Determine whether the collision is horizontal or vertical
	if (fabs(minOverlapX) < fabs(minOverlapY) || fabs(minOverlapX) == fabs(minOverlapY))
	{
		// Horizontal collision
		velSelf.x = -velSelf.x;
		// Separate the ball by a small amount
		posSelf.position.x += fromLeft ? -minOverlapX : minOverlapX;
	}
	else
	{
		// Vertical collision
		velSelf.y = -velSelf.y;
		// Separate the ball by a small amount
		posSelf.position.y += fromTop ? -minOverlapY : minOverlapY;
	}
};

void CreateBallEntity(std::string entity_name, std::string scene_name)
{
	SDL_Texture *texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);

	// Find another way to get a random velocity direction
	float velX = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
	// velY is not always the same
	int factor = rand() % BALL_SPEED + 1;
	// Up or down (random)
	float velY = (rand() % 2 == 0 ? -factor : factor);

	Entity entity = Game::coordinator.CreateEntity(entity_name, scene_name);

	Game::coordinator.AddComponent(
		entity,
		TransformComponent{
			Vec2(SCREEN_WIDTH / 2 - BALL_SIZE / 2,
				 SCREEN_HEIGHT / 2 - BALL_SIZE / 2)});
	Game::coordinator.AddComponent(
		entity,
		VelocityComponent{
			velX, // X
			velY  // Y
		});
	Game::coordinator.AddComponent(
		entity,
		SpriteComponent{
			texture, // Texture
			{
				// Source rectangle
				42,		   // X
				5,		   // Y
				BALL_SIZE, // W
				BALL_SIZE  // H
			},
			{
				// Destination rectangle
				0,		   // X
				0,		   // Y
				BALL_SIZE, // W
				BALL_SIZE  // H
			},
			SDL_FLIP_NONE // Flip
		});
	Game::coordinator.AddComponent(
		entity,
		CollisionComponent{
			{0, 0, BALL_SIZE, BALL_SIZE},
			ballCollisionCallback});
}