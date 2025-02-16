#pragma once

#include <functional>
#include "../Utils/GameEnums.h"
#include "../Utils/BrickUtils.h"

auto brickCollisionCallback = [](Entity self, Entity other)
{
	Core::coordinator.MarkEntityForDeletion(self);
};

void CreateBrickEntity(std::string entity_name, std::string scene_name, Vec2 pos, int brickType)
{
	SDL_Texture *texture = TextureManager::LoadTexture(BRICKS_SPRITE_FILEPATH);

	BrickType type = static_cast<BrickType>(brickType);
	SDL_Rect srcRect = GetBrickSrcRect(type);

	Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);

	Core::coordinator.AddComponent(
		entity,
		TransformComponent{ pos });
	Core::coordinator.AddComponent(
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
	Core::coordinator.AddComponent(
		entity,
		RigidBodyComponent{
			{0, 0, BRICK_WIDTH, BRICK_HEIGHT}, // Collider
			Vec2(0, 0),						   // Velocity
			Vec2(0, 0),						   // Acceleration
			1.0f,							   // Mass
			true,							   // Is static?
			false,							   // Use gravity?
			brickCollisionCallback});
}