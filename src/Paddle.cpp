#include "Paddle.h"

Paddle::Paddle(int x, int y)
{
    rect.x = x;
    rect.y = y;
    rect.w = 20;  // Ancho del paddle
    rect.h = 100; // Altura del paddle
}

void Paddle::moveUp()
{
    if (rect.y > 0)
    {
        rect.y -= PADDLE_SPEED;
    }
}

void Paddle::moveDown()
{
    if (rect.y + rect.h < SCREEN_HEIGHT)
    {
        rect.y += PADDLE_SPEED;
    }
}

SDL_Rect Paddle::getRect() const
{
    return rect;
}

void Paddle::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco
    SDL_RenderFillRect(renderer, &rect);
}
