#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../../Utils/TextureManager.h"
#include "../Component/Background/TileBackgroundComponent.h"
#include "../Component/Background/SolidColorBackgroundComponent.h"
#include "../Component/Background/ImageBackgroundComponent.h"
#include "../Component/Background/ParallaxBackgroundComponent.h"

Entity CreateTileBackgroundEntity()
{
	// Load the tile texture
	SDL_Texture *tileTexture = TextureManager::LoadTexture(BGS_SPRITE_FILEPATH);

	// Tile texture dimensions
	int tileTextureWidth = 160;
	int tileTextureHeight = 32;

	// Dimensions of each tile
	int tileWidth = 32;
	int tileHeight = 32;

	// Dimensions of the tile map (how many tiles in width and height)
	int mapWidth = SCREEN_WIDTH / tileWidth;
	int mapHeight = SCREEN_HEIGHT / tileHeight;

	std::vector<int> tiles(mapWidth * mapHeight, 0);

	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, TileBackgroundComponent{tileTexture, tileTextureWidth, tileTextureHeight, tileWidth, tileHeight, mapWidth, mapHeight, tiles});
	return entity;
}

Entity CreateSolidColorBackgroundEntity(SDL_Color color)
{
	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, SolidColorBackgroundComponent{color});
	return entity;
}

Entity CreateImageBackgroundEntity(SDL_Texture *imageTexture, int width, int height)
{
	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, ImageBackgroundComponent{imageTexture, width, height});
	return entity;
}

Entity CreateParallaxBackgroundEntity(std::vector<ParallaxLayer> layers)
{
	Entity entity = Game::coordinator.CreateEntity();
	Game::coordinator.AddComponent(entity, ParallaxBackgroundComponent{layers});
	return entity;
}
