#pragma once
#include "System.h"
#include "PositionComponent.h"
#include "RenderComponent.h"

class RenderSystem : public System
{
public:
    void Update(float deltaTime) override
    {
        // No necesita actualización lógica
    }

    void Render(SDL_Renderer *renderer) override
    {
        // Lógica para renderizar entidades con PositionComponent y RenderComponent
    }
};
