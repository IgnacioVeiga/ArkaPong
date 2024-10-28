#pragma once

void CreateAnimatedEntity(std::string entity_name, std::string scene_name, const std::string& texturePath, int frameCount, int frameWidth, int frameHeight, int animationSpeed, bool loop, float posX, float posY)
{
	Entity entity = Game::coordinator.CreateEntity(entity_name, scene_name);

	SDL_Texture* texture = TextureManager::LoadTexture(texturePath.c_str());
	Game::coordinator.AddComponent(
		entity,
		TransformComponent{Vec2(posX, posY)});
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

	std::shared_ptr<BasePath> movementScript = std::make_shared<CircularPath>(
		(SCREEN_WIDTH / 2) - 8,		// Center X
		(SCREEN_HEIGHT / 2) - 8,	// Center Y
		64.0f,						// Radius
		1.0f						// Speed
	);

	std::vector<PathEvent> events = {};

	Game::coordinator.AddComponent(entity, PathComponent{ movementScript, events });
}
