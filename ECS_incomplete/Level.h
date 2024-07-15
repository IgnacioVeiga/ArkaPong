#pragma once
#include <vector>
#include <SDL2/SDL.h>
#include "Entity.h"

class Level
{
public:
    void Load();
    void Update(float deltaTime);
    void Render(SDL_Renderer *renderer);

private:
    std::vector<Entity> entities;
};
