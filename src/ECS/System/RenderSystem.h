#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/RenderComponent.h"
#include "../Component/PositionComponent.h"
#include "../../Utils/GameConstants.h"

// Rename to SpriteSystem?
class RenderSystem : public System
{
public:
    void Init()
    {
        Signature signature;
        signature.set(Game::coordinator.GetComponentType<RenderComponent>());
        Game::coordinator.SetSystemSignature<RenderSystem>(signature);
    }

    void Update()
    {
        for (auto const &entity : mEntities)
        {
            auto &renderComponent = Game::coordinator.GetComponent<RenderComponent>(entity);
            auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

            SDL_FRect destRect = {
                positionComponent.x,        // X
                positionComponent.y,        // Y
                renderComponent.destRect.w, // W
                renderComponent.destRect.h  // H
            };

            SDL_RenderCopyExF(
                Game::renderer,           // Renderer
                renderComponent.texture,  // Texture
                &renderComponent.srcRect, // Source rectangle
                &destRect,                // Destination rectangle
                0.0,                      // Angle
                nullptr,                  // Center
                renderComponent.flip      // Flip
            );
        }

        // DEBUG, remove later
        DrawGrid(Game::renderer, SCREEN_WIDTH, SCREEN_HEIGHT, CELL_GRID_SIZE);
    }

    void DrawGrid(SDL_Renderer *renderer, int gridWidth, int gridHeight, int cellSize)
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE); // Color rojo para las líneas del grid

        // Dibujar líneas verticales
        for (int x = 0; x <= gridWidth; x += cellSize)
        {
            SDL_RenderDrawLine(renderer, x, 0, x, gridHeight);
        }

        // Dibujar líneas horizontales
        for (int y = 0; y <= gridHeight; y += cellSize)
        {
            SDL_RenderDrawLine(renderer, 0, y, gridWidth, y);
        }
    }
};