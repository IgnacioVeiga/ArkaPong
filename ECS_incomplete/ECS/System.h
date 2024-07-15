#pragma once

#include "SDL.h"

class System
{
public:
    virtual ~System() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer *renderer) = 0;
};
