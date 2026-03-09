#pragma once
#include "Core/Utils/CoreConstants.h"

class SpriteSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<SpriteComponent>());
        signature.set(Core::GetCoordinator().GetComponentType<TransformComponent>());
        Core::GetCoordinator().SetSystemSignature<SpriteSystem>(signature);
    }

    void Update() {
        for (auto const &entity: mEntities) {
            auto &spriteComponent = Core::GetCoordinator().GetComponent<SpriteComponent>(entity);
            auto &transformComponent = Core::GetCoordinator().GetComponent<TransformComponent>(entity);
            const float scaleX = transformComponent.scale.x == 0.0f ? 1.0f : transformComponent.scale.x;
            const float scaleY = transformComponent.scale.y == 0.0f ? 1.0f : transformComponent.scale.y;

            SDL_FRect destRect = {
                transformComponent.position.x, // X
                transformComponent.position.y, // Y
                spriteComponent.destRect.w * scaleX, // W
                spriteComponent.destRect.h * scaleY // H
            };

            SDL_RenderCopyExF(
                Core::GetWindow().GetRenderer(), // Renderer
                spriteComponent.texture, // Texture
                &spriteComponent.srcRect, // Source rectangle
                &destRect, // Destination rectangle
                transformComponent.rotation, // Angle
                nullptr, // Center
                spriteComponent.flip // Flip
            );
        }

        // DEBUG, remove later
        DrawGrid(
            Core::GetWindow().GetRenderer(),
            Core::GetWindow().GetLogicalWidth(),
            Core::GetWindow().GetLogicalHeight(),
            CELL_GRID_SIZE);
    }

    void DrawGrid(SDL_Renderer *renderer, const int gridWidth, const int gridHeight, const int cellSize) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        for (int x = 0; x <= gridWidth; x += cellSize) {
            SDL_RenderDrawLine(renderer, x, 0, x, gridHeight);
        }
        for (int y = 0; y <= gridHeight; y += cellSize) {
            SDL_RenderDrawLine(renderer, 0, y, gridWidth, y);
        }
    }
};
