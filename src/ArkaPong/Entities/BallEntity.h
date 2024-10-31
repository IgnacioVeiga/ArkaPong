#pragma once

#include <functional>

auto ballCollisionCallback = [](Entity self, Entity other)
{
	auto &transform_self = Game::coordinator.GetComponent<TransformComponent>(self);
	auto &rigidbody_self = Game::coordinator.GetComponent<RigidBodyComponent>(self);

	auto &transform_other = Game::coordinator.GetComponent<TransformComponent>(other);
	auto &rigidbody_other = Game::coordinator.GetComponent<RigidBodyComponent>(other);

	// Calculate overlap on each side of the collision
	float overlapLeft = (transform_self.position.x + rigidbody_self.collider.w) - transform_other.position.x;
	float overlapRight = (transform_other.position.x + rigidbody_other.collider.w) - transform_self.position.x;
	float overlapTop = (transform_self.position.y + rigidbody_self.collider.h) - transform_other.position.y;
	float overlapBottom = (transform_other.position.y + rigidbody_other.collider.h) - transform_self.position.y;

	// Determine which side the collision is coming from
	bool fromLeft = fabs(overlapLeft) < fabs(overlapRight);
	bool fromTop = fabs(overlapTop) < fabs(overlapBottom);

	// Find the minimum overlap in the X and Y axes
	float minOverlapX = fromLeft ? overlapLeft : overlapRight;
	float minOverlapY = fromTop ? overlapTop : overlapBottom;

	// Determine whether the collision is horizontal or vertical
	if (fabs(minOverlapX) < fabs(minOverlapY))
	{
		// Horizontal collision
		rigidbody_self.velocity.x = -rigidbody_self.velocity.x;
		// Separate the ball by a small amount
		transform_self.position.x += fromLeft ? -minOverlapX : minOverlapX;
	}
	else if (fabs(minOverlapX) > fabs(minOverlapY))
	{
		// Vertical collision
		rigidbody_self.velocity.y = -rigidbody_self.velocity.y;
		// Separate the ball by a small amount
		transform_self.position.y += fromTop ? -minOverlapY : minOverlapY;
	}
	else
	{
		// Diagonal collision
		rigidbody_self.velocity.x = -rigidbody_self.velocity.x;
		rigidbody_self.velocity.y = -rigidbody_self.velocity.y;
		// Separate the ball by a small amount
		transform_self.position.y += fromTop ? -minOverlapY : minOverlapY;
		transform_self.position.x += fromLeft ? -minOverlapX : minOverlapX;
	}
};

void CreateBallEntity(std::string entity_name, std::string scene_name)
{
	SDL_Texture *texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);

	// Find another way to get a random velocity direction
	float velX = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
	// velY is not always the same
	float factor = static_cast<float>(rand() % static_cast<int>(BALL_SPEED) + 1);
	// Up or down (random)
	float velY = (rand() % 2 == 0 ? -factor : factor);
	Vec2 velocity = Vec2(velX, velY);

	Entity entity = Game::coordinator.CreateEntity(entity_name, scene_name);

	Game::coordinator.AddComponent(
		entity,
		TransformComponent{
			Vec2(SCREEN_WIDTH / 2 - BALL_SIZE / 2,
				 SCREEN_HEIGHT / 2 - BALL_SIZE / 2)});
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
		RigidBodyComponent{
			{0, 0, BALL_SIZE, BALL_SIZE}, // Collider
			velocity,
			Vec2(0, 0), // Acceleration
			1.0f,		// Mass
			false,		// Is static?
			false,		// Use gravity?
			ballCollisionCallback});
}