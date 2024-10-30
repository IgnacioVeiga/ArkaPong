#pragma once

#include <functional>
#include "../../Core/Manager/TextureManager.h"

auto paddleCollisionCallback = [](Entity self, Entity other)
{
	// TODO: do collision logic with walls, enemies or something like that.
};

auto goUpCallback = [](Entity self)
{
	auto &transformComponent = Game::coordinator.GetComponent<TransformComponent>(self);
	auto &rigidBodyComponent = Game::coordinator.GetComponent<RigidBodyComponent>(self);

	transformComponent.position.y = std::max(0.0f, transformComponent.position.y - rigidBodyComponent.velocity.y);
};

auto goDownCallback = [](Entity self)
{
	auto &transformComponent = Game::coordinator.GetComponent<TransformComponent>(self);
	auto &rigidBodyComponent = Game::coordinator.GetComponent<RigidBodyComponent>(self);

	transformComponent.position.y = std::min(static_cast<float>(SCREEN_HEIGHT - PADDLE_HEIGHT), transformComponent.position.y + rigidBodyComponent.velocity.y);
};

void CreatePaddleEntity(std::string entity_name, std::string scene_name, Side side)
{
	SDL_Texture *texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);
	SDL_Rect srcRectPaddle = {
		0,			  // X
		0,			  // Y
		PADDLE_WIDTH, // W
		PADDLE_HEIGHT // H
	};

	float x_position = (side == Side::LEFT) ? PADDLE_OFFSET : (SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH);
	SDL_RendererFlip flip = (side == Side::LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

	SDL_Keycode upKeyCode = (side == Side::LEFT) ? SDL_SCANCODE_W : SDL_SCANCODE_UP;
	SDL_Keycode downKeyCode = (side == Side::LEFT) ? SDL_SCANCODE_S : SDL_SCANCODE_DOWN;

	std::vector<InputBehavior> keyMappings = {
		{upKeyCode, goUpCallback},
		{downKeyCode, goDownCallback}};

	Vec2 velocity = Vec2(0, PADDLE_SPEED);

	Entity entity = Game::coordinator.CreateEntity(entity_name, scene_name);
	Game::coordinator.AddComponent(
		entity,
		TransformComponent{
			Vec2(x_position, SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2)});
	Game::coordinator.AddComponent(
		entity,
		SpriteComponent{
			texture,	   // Texture
			srcRectPaddle, // Source rectangle
			{
				// Destination rectangle
				0,			  // X
				0,			  // Y
				PADDLE_WIDTH, // W
				PADDLE_HEIGHT // H
			},
			flip});
	Game::coordinator.AddComponent(
		entity,
		RigidBodyComponent{
			{0, 0, PADDLE_WIDTH, PADDLE_HEIGHT}, // Collider
			velocity,
			Vec2(0, 0), // Acceleration
			1.0f,		// Mass
			true,		// Is it static? Yes, because it only moves vertically
			false,		// Use gravity?
			paddleCollisionCallback});
	Game::coordinator.AddComponent(
		entity,
		InputComponent{keyMappings, 5});
}