#pragma once

#include <functional>
#include <SDL2/SDL.h>

struct CollisionComponent
{
    SDL_Rect collider;
    std::function<void(Entity self, Entity other)> onCollision; // Callback for custom behavior
};
