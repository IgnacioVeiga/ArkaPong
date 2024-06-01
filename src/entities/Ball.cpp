#include "Ball.h"
#include <cstdlib>
#include <ctime>
#include "../managers/TextureManager.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"

Ball::Ball() : velX(BALL_SPEED), velY(BALL_SPEED)
{
    texture = TextureManager::LoadTexture("assets/sprites/ball.bmp");

    // Rectangle where the texture is rendered
    rect = {
        SCREEN_WIDTH / 2 - BALL_SIZE / 2,  // X
        SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // Y
        BALL_SIZE,                         // W
        BALL_SIZE                          // H
    };
}

Ball::~Ball()
{
    SDL_DestroyTexture(texture);
}

void Ball::move()
{
    rect.x += velX;
    rect.y += velY;
}

void Ball::center()
{
    rect.x = SCREEN_WIDTH / 2;
    rect.y = SCREEN_HEIGHT / 2;

    // To left or right (random)
    velX = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
    // velY is not always the same
    int factor = rand() % BALL_SPEED + 1;
    // Up or down (random)
    velY = (rand() % 2 == 0 ? -factor : factor);
}

void Ball::render()
{
    if (texture)
    {
        SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
    }
    else
    {
        // Drawing fallback in case texture is not available
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(Game::renderer, &rect);
    }
}

const SDL_Rect &Ball::getRect() const
{
    return rect;
}