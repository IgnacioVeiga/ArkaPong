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
			BALL_SPEED, // X
			BALL_SPEED	// Y
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