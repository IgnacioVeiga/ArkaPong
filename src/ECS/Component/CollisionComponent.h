#pragma once

#include <SDL2/SDL.h>

enum class CollisionSide
{
    NONE,
    RIGHT,
    TOP,
    BOTTOM,
    LEFT
};

struct CollisionComponent
{
    SDL_Rect collider;
    CollisionSide collisionSide = CollisionSide::NONE;
};