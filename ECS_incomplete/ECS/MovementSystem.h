#pragma once
#include "System.h"
#include "PositionComponent.h"

class MovementSystem : public System
{
public:
    void Update(float deltaTime) override
    {
        // Lógica para actualizar las entidades con PositionComponent
    }

    void Render(SDL_Renderer *renderer) override
    {
        // No necesita renderizado
    }
};
