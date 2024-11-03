#pragma once

#include <functional>

auto ballCollisionCallback = [](Entity self, Entity other)
{
	// TODO: bounce sfx sound
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

	Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);

	Core::coordinator.AddComponent(
		entity,
		TransformComponent{
			Vec2(SCREEN_WIDTH / 2 - BALL_SIZE / 2,
				 SCREEN_HEIGHT / 2 - BALL_SIZE / 2)});
	Core::coordinator.AddComponent(
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
	Core::coordinator.AddComponent(
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