#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../Component/PositionComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/CollisionComponent.h"
#include "../../Utils/Constants.h"
#include "../../Utils/TextureManager.h"
#include "../../Utils/BrickUtils.h"

auto brickCollisionCallback = [](Entity self, Entity other)
{
	// TODO: logic “destroy or not” here.
};

Entity CreateBrickEntity(float posX, float posY, int brickType)
{
	SDL_Texture *texture = TextureManager::LoadTexture(BRICKS_SPRITE_FILEPATH);

	BrickType type = static_cast<BrickType>(brickType);
	SDL_Rect srcRect = GetBrickSrcRect(type);

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
			srcRect,
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
			},
			brickCollisionCallback});

	return entity;
}