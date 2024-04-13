#include <algorithm>
#include "Paddle.h"
#include "GameConstants.h"

Paddle::Paddle(SDL_Renderer *renderer, int x, int y, int w, int h) : renderer(renderer)
{
    rect = {x, y, w, h};
}

void Paddle::moveUp()
{
    rect.y = std::max(0, rect.y - 10);
}

void Paddle::moveDown()
{
    rect.y = std::min(SCREEN_HEIGHT - rect.h, rect.y + 10);
}

void Paddle::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco
    SDL_RenderFillRect(renderer, &rect);
}

const SDL_Rect &Paddle::getRect() const
{
    return rect;
}