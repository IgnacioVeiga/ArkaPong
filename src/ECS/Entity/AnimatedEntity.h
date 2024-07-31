#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../../Utils/TextureManager.h"
#include "../../Utils/Events.h"
#include "../Component/AnimationComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/MovementScriptComponent.h"

Entity CreateAnimatedEntity(const std::string& texturePath, int frameCount, int frameWidth, int frameHeight, int animationSpeed, bool loop, float posX, float posY)
{
	Entity entity = Game::coordinator.CreateEntity();

	SDL_Texture* texture = TextureManager::LoadTexture(texturePath.c_str());
	Game::coordinator.AddComponent(
		entity,
		PositionComponent{
			posX, // X
			posY  // Y
		});
	Game::coordinator.AddComponent(
		entity,
		SpriteComponent{
			texture,
			{0, 0, frameWidth, frameHeight}, // Source rectangle
			{0, 0, static_cast<float>(frameWidth), static_cast<float>(frameHeight)},
			SDL_FLIP_NONE });

	Game::coordinator.AddComponent(
		entity,
		AnimationComponent{
			0,              // currentFrame
			frameCount,     // frameCount
			frameWidth,     // frameWidth
			frameHeight,    // frameHeight
			animationSpeed, // animationSpeed
			0,              // elapsedTime
			loop,           // loop
			true            // isPlaying
		});

	std::shared_ptr<BaseMovementScript> movementScript = std::make_shared<CircularMovementScript>(
		(SCREEN_WIDTH / 2) - 8,		// Center X
		(SCREEN_HEIGHT / 2) - 8,	// Center Y
		64.0f,						// Radius
		1.0f						// Speed
	);

	//std::shared_ptr<BaseMovementScript> movementScript = std::make_shared<LinearMovementScript>(50.0f, 0.0f);

	std::vector<MovementEvent> events = {
		/*{posX + 100, posY, TriggerAction}*/
	};

	Game::coordinator.AddComponent(entity, MovementScriptComponent{ movementScript, events });

	return entity;
}
