#pragma once

#include <functional>
#include "../Utils/GameEnums.h"
#include "../BrickUtils.h"

auto brickCollisionCallback = [](Entity self, Entity other)
{
	Game::coordinator.MarkEntityForDeletion(self);
};

void CreateBrickEntity(std::string entity_name, std::string scene_name, float posX, float posY, int brickType)
{
	SDL_Texture *texture = TextureManager::LoadTexture(BRICKS_SPRITE_FILEPATH);

	BrickType type = static_cast<BrickType>(brickType);
	SDL_Rect srcRect = GetBrickSrcRect(type);

	Entity entity = Game::coordinator.CreateEntity(entity_name, scene_name);

	Game::coordinator.AddComponent(
		entity,
		TransformComponent{Vec2(posX, posY)});
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
}