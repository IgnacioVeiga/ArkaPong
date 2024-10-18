#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/SpriteComponent.h"
#include "../Component/PositionComponent.h"
#include "../../Utils/Constants.h"

class SpriteSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<SpriteComponent>());
		Game::coordinator.SetSystemSignature<SpriteSystem>(signature);
	}

	void Update()
	{
		for (auto const& entity : mEntities)
		{
			auto& spriteComponent = Game::coordinator.GetComponent<SpriteComponent>(entity);
			auto& positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

			SDL_FRect destRect = {
				positionComponent.x,        // X
				positionComponent.y,        // Y
				spriteComponent.destRect.w, // W
				spriteComponent.destRect.h  // H
			};

			SDL_RenderCopyExF(
				Game::window.GetRenderer(), // Renderer
				spriteComponent.texture,        // Texture
				&spriteComponent.srcRect,       // Source rectangle
				&destRect,                      // Destination rectangle
				0.0,                            // Angle
				nullptr,                        // Center
				spriteComponent.flip            // Flip
			);
		}

		// DEBUG, remove later
		DrawGrid(Game::window.GetRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT, CELL_GRID_SIZE);
	}

	void DrawGrid(SDL_Renderer* renderer, int gridWidth, int gridHeight, int cellSize)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		for (int x = 0; x <= gridWidth; x += cellSize)
		{
			SDL_RenderDrawLine(renderer, x, 0, x, gridHeight);
		}
		for (int y = 0; y <= gridHeight; y += cellSize)
		{
			SDL_RenderDrawLine(renderer, 0, y, gridWidth, y);
		}
	}
};