#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/CollisionComponent.h"
#include "../Component/InputComponent.h"
#include "../../Utils/Constants.h"
#include "../../Utils/Enums.h"
#include "../../Utils/TextureManager.h"
#include <vector>

auto paddleCollisionCallback = [](Entity self, Entity other)
{
	// TODO: do collision logic with walls, enemies or something like that.
};

auto goUpCallback = [](Entity self)
{
	auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(self);
	auto &velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(self);

	positionComponent.y = std::max(0.0f, positionComponent.y - velocityComponent.y);
};

auto goDownCallback = [](Entity self)
{
	auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(self);
	auto &velocityComponent = Game::coordinator.GetComponent<VelocityComponent>(self);

	positionComponent.y = std::min(static_cast<float>(SCREEN_HEIGHT - PADDLE_HEIGHT), positionComponent.y + velocityComponent.y);
};

Entity CreatePaddleEntity(Side side)
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

	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(
		entity,
		PositionComponent{
			x_position,							  // X
			SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2 // Y
		});
	Game::coordinator.AddComponent(
		entity,
		VelocityComponent{
			0,			 // X
			PADDLE_SPEED // Y
		});
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
		CollisionComponent{
			{
				// Collider rectangle
				0,			  // X
				0,			  // Y
				PADDLE_WIDTH, // W
				PADDLE_HEIGHT // H
			},
			paddleCollisionCallback});
	Game::coordinator.AddComponent(
		entity,
		InputComponent{keyMappings});

	return entity;
}