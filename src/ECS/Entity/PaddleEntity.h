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

enum class PlayerSide
{
	PLAYER_LEFT,
	PLAYER_RIGHT
};

Entity CreatePaddleEntity(PlayerSide side)
{
	SDL_Texture* texture = TextureManager::LoadTexture("assets/sprites/vaus.bmp");
	SDL_Rect srcRectPaddle = {
		0,			  // X
		0,			  // Y
		PADDLE_WIDTH, // W
		PADDLE_HEIGHT // H
	};

	float x_position = (side == PlayerSide::PLAYER_LEFT) ? PADDLE_OFFSET : (SCREEN_WIDTH - PADDLE_OFFSET - PADDLE_WIDTH);
	SDL_RendererFlip flip = (side == PlayerSide::PLAYER_LEFT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
	SDL_Keycode upKeyCode = (side == PlayerSide::PLAYER_LEFT) ? SDL_SCANCODE_W : SDL_SCANCODE_UP;
	SDL_Keycode downKeyCode = (side == PlayerSide::PLAYER_LEFT) ? SDL_SCANCODE_S : SDL_SCANCODE_DOWN;

	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(
		entity,
		PositionComponent{
			x_position,								// X
			SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2	// Y
		});
	Game::coordinator.AddComponent(
		entity,
		VelocityComponent{
			0,			 // X
			PADDLE_SPEED // Y
		}
	);
	Game::coordinator.AddComponent(
		entity,
		CollisionComponent{
			{
				// Collider rectangle
				0,			  // X
				0,			  // Y
				PADDLE_WIDTH, // W
				PADDLE_HEIGHT // H
			}
		}
	);
	Game::coordinator.AddComponent(
		entity,
		SpriteComponent{
			texture,	   // Texture
			srcRectPaddle, // Source rectangle
			{
			// Destination rectangle
			0,				// X
			0,				// Y
			PADDLE_WIDTH,	// W
			PADDLE_HEIGHT	// H
		},
		flip
		});
	Game::coordinator.AddComponent(
		entity,
		InputComponent{
			{{"up", upKeyCode}, {"down", downKeyCode}}, // Key mappings
			{{upKeyCode, false}, {downKeyCode, false}}	// Key states
		});

	return entity;
}