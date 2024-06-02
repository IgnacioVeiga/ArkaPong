#pragma once

#include <SDL2/SDL_scancode.h>

struct PositionComponent
{
    float x, y;
};

struct VelocityComponent
{
    float x, y;
};

struct RenderComponent
{
    SDL_Texture *texture;
    SDL_Rect rect;
};

struct InputComponent
{
    SDL_Scancode upKey;
    SDL_Scancode downKey;
};

struct MovementComponent
{
    float speed;
};
