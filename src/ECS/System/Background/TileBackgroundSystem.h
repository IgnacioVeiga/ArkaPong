#pragma once

#include "../../../Game.h"
#include "../../Coordinator.h"
#include "../../Component/Background/TileBackgroundComponent.h"
#include "../../Component/PositionComponent.h"

/*
	Example of how to use:
	SDL_Texture* tileTexture = TextureManager::LoadTexture("path/to/tile_texture.png");
	int tileTextureWidth = 160; // Mosaic texture width
	int tileTextureHeight = 32; // Mosaic texture height
	int tileWidth = 32;
	int tileHeight = 32;
	int mapWidth = 5;  // Mosaic background map width
	int mapHeight = 5; // Height of the background map in mosaics
    std::vector<int> tiles(vector size, value to be used for all elements.);
	Entity tileBackground = CreateTileBackgroundEntity(tileTexture, tileTextureWidth, tileTextureHeight, tileWidth, tileHeight, mapWidth, mapHeight, tiles);
*/
class TileBackgroundSystem : public System {
public:
	void Init() {
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<TileBackgroundComponent>());
		Game::coordinator.SetSystemSignature<TileBackgroundSystem>(signature);
	}

    void Update()
    {
        for (auto const& entity : mEntities)
        {
            auto& bg = Game::coordinator.GetComponent<TileBackgroundComponent>(entity);
            SDL_Rect srcRect;
            SDL_FRect destRect;

            int tilesPerRow = bg.tileTextureWidth / bg.tileWidth;
            for (int y = 0; y < bg.mapHeight; ++y)
            {
                for (int x = 0; x < bg.mapWidth; ++x)
                {
                    int tileIndex = bg.tiles[y * bg.mapWidth + x];
                    srcRect.x = (tileIndex % tilesPerRow) * bg.tileWidth;
                    srcRect.y = (tileIndex / tilesPerRow) * bg.tileHeight;
                    srcRect.w = bg.tileWidth;
                    srcRect.h = bg.tileHeight;

                    destRect.x = x * bg.tileWidth;
                    destRect.y = y * bg.tileHeight;
                    destRect.w = bg.tileWidth;
                    destRect.h = bg.tileHeight;

                    SDL_RenderCopyF(Game::renderer, bg.tileTexture, &srcRect, &destRect);
                }
            }
        }
    }
};
