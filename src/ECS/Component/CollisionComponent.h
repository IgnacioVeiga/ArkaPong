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

enum class ColliderType
{
    STATIC, // Ex:  Walls, bricks, etc.
    DYNAMIC // Ex:  Ball
};

struct CollisionComponent
{
    SDL_Rect collider;
    ColliderType type = ColliderType::DYNAMIC;
    Side collisionSide = Side::NONE;
};
