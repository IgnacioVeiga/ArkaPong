#include "Ball.h"
#include "GameConstants.h"
#include <SDL2/SDL.h>

Ball::Ball(SDL_Renderer *renderer, int x, int y, int w, int h) : renderer(renderer), velX(BALL_SPEED), velY(BALL_SPEED)
{
    rect = {x, y, w, h};
}

void Ball::move()
{
    rect.x += velX;
    rect.y += velY;

    if (rect.y <= 0 || rect.y + rect.h >= SCREEN_HEIGHT)
    {
        velY = -velY;
    }
}

void Ball::reset(int x, int y)
{
    rect.x = x;
    rect.y = y;
}

void Ball::changeDirection(Paddle &paddle)
{
    if (SDL_HasIntersection(&rect, &paddle.getRect()))
    {
        velX = -velX;
        int paddleCenter = paddle.getRect().y + paddle.getRect().h / 2;
        int ballCenter = rect.y + rect.h / 2;
        velY = (ballCenter - paddleCenter) / 15; // Adjust Y velocity based on hit position
    }
}

void Ball::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco
    SDL_RenderFillRect(renderer, &rect);
}

bool Ball::checkCollision(const SDL_Rect& paddleRect) {
    // Comprueba si hay colisión entre la pelota y un paddle
    if (SDL_HasIntersection(&rect, &paddleRect)) {
        return true;
    }
    return false;
}