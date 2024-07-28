#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../Component/Background/TileBackgroundComponent.h"
#include "../Component/Background/SolidColorBackgroundComponent.h"
#include "../Component/Background/ImageBackgroundComponent.h"
#include "../Component/Background/ParallaxBackgroundComponent.h"

Entity CreateTileBackgroundEntity(SDL_Texture* tileTexture, int tileTextureWidth, int tileTextureHeight, int tileWidth, int tileHeight, int mapWidth, int mapHeight, std::vector<int> tiles) {
	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, TileBackgroundComponent{ tileTexture, tileTextureWidth, tileTextureHeight, tileWidth, tileHeight, mapWidth, mapHeight, tiles });
	return entity;
}

Entity CreateSolidColorBackgroundEntity(SDL_Color color) {
	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, SolidColorBackgroundComponent{ color });
	return entity;
}

Entity CreateImageBackgroundEntity(SDL_Texture* imageTexture, int width, int height) {
	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, ImageBackgroundComponent{ imageTexture, width, height });
	return entity;
}

Entity CreateParallaxBackgroundEntity(std::vector<ParallaxLayer> layers) {
	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, ParallaxBackgroundComponent{ layers });
	return entity;
}
