#pragma once

#include <functional>

struct CollisionComponent
{
    SDL_Rect collider;
    std::function<void(Entity self, Entity other)> onCollision; // Callback for custom behavior
};
