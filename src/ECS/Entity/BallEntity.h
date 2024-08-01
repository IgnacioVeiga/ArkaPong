#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/CollisionComponent.h"
#include "../Component/InputComponent.h"
#include "../../Utils/GameConstants.h"
#include "../../Utils/TextureManager.h"

Entity CreateBallEntity()
{
	SDL_Texture* texture = TextureManager::LoadTexture(VAUS_SPRITE_FILEPATH);

	// Find another way to get a random velocity direction
	float velX = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
	// velY is not always the same
	int factor = rand() % BALL_SPEED + 1;
	// Up or down (random)
	float velY = (rand() % 2 == 0 ? -factor : factor);

	Entity entity = Game::coordinator.CreateEntity();

	Game::coordinator.AddComponent(
		entity,
		PositionComponent{
			SCREEN_WIDTH / 2 - BALL_SIZE / 2,  // X
			SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // Y
		});
	Game::coordinator.AddComponent(
		entity,
		VelocityComponent{
			velX,	// X
			velY	// Y
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
			0,			// X
			0,			// Y
			BALL_SIZE,	// W
			BALL_SIZE	// H
		},
		SDL_FLIP_NONE // Flip
		});
	Game::coordinator.AddComponent(
		entity,
		CollisionComponent{
			{
				// Collider rectangle
				0,		   // X
				0,		   // Y
				BALL_SIZE, // W
				BALL_SIZE  // H
			}
		}
	);

	return entity;
}