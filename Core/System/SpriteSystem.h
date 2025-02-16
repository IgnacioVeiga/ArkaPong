#pragma once

class SpriteSystem : public System
{
public:
	void Init()
	{
		Signature signature{};
		signature.set(Core::coordinator.GetComponentType<SpriteComponent>());
		signature.set(Core::coordinator.GetComponentType<TransformComponent>());
		Core::coordinator.SetSystemSignature<SpriteSystem>(signature);
	}

	void Update()
	{
		for (auto const &entity : mEntities)
		{
			auto &spriteComponent = Core::coordinator.GetComponent<SpriteComponent>(entity);
			auto &transformComponent = Core::coordinator.GetComponent<TransformComponent>(entity);

			SDL_FRect destRect = {
				transformComponent.position.x, // X
				transformComponent.position.y, // Y
				spriteComponent.destRect.w,	   // W
				spriteComponent.destRect.h	   // H
			};

			SDL_RenderCopyExF(
				Core::window.GetRenderer(), // Renderer
				spriteComponent.texture,	// Texture
				&spriteComponent.srcRect,	// Source rectangle
				&destRect,					// Destination rectangle
				0.0,						// Angle
				nullptr,					// Center
				spriteComponent.flip		// Flip
			);
		}

		// DEBUG, remove later
		DrawGrid(Core::window.GetRenderer(), SCREEN_WIDTH, SCREEN_HEIGHT, CELL_GRID_SIZE);
	}

	void DrawGrid(SDL_Renderer *renderer, int gridWidth, int gridHeight, int cellSize)
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