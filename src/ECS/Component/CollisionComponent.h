#pragma once

#include <SDL2/SDL.h>

enum class Side
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
    Side collisionSide = Side::NONE;
};