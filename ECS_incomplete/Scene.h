#pragma once
#include "SDL.h"

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Load() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer *renderer) = 0;
};
