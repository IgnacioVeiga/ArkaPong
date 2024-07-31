#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../Component/PositionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/CollisionComponent.h"
#include "../../Utils/GameConstants.h"
#include "../../Utils/TextureManager.h"

Entity CreateBrickEntity(float posX, float posY, int srcRectX = 0, int srcRectY = 0)
{
	SDL_Texture *texture = TextureManager::LoadTexture(BRICKS_SPRITE_FILEPATH);

	Entity entity = Game::coordinator.CreateEntity();

	Game::coordinator.AddComponent(
		entity,
		PositionComponent{
			posX, // X
			posY, // Y
		});
	Game::coordinator.AddComponent(
		entity,
		SpriteComponent{
			texture, // Texture
			{
				// Source rectangle
				srcRectX,	 // X
				srcRectY,	 // Y
				BRICK_WIDTH, // W
				BRICK_HEIGHT // H
			},
			{
				// Destination rectangle
				0,			 // X
				0,			 // Y
				BRICK_WIDTH, // W
				BRICK_HEIGHT // H
			},
			SDL_FLIP_NONE // Flip
		});
	Game::coordinator.AddComponent(
		entity,
		CollisionComponent{
			{
				// Collider rectangle
				0,			 // X
				0,			 // Y
				BRICK_WIDTH, // W
				BRICK_HEIGHT // H
			}});

	return entity;
}