#include "Paddle.h"
#include <algorithm>
#include "../managers/TextureManager.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"

Paddle::Paddle(PlayerSide side) : side(side)
{
    texture = TextureManager::LoadTexture("assets/sprites/paddle.bmp");

    int x = (side == PlayerSide::PLAYER_LEFT) ? PADDLE_OFFSET : SCREEN_WIDTH - PADDLE_OFFSET;
    // Rectangle used for the position and the colider
    rect = {
        x,                                     // X
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, // Y
        PADDLE_WIDTH,                          // W
        PADDLE_HEIGHT                          // H
    };
}

Paddle::~Paddle()
{
    SDL_DestroyTexture(texture);
}

void Paddle::moveUp()
{
    rect.y = std::max(0, rect.y - PADDLE_SPEED);
}

void Paddle::moveDown()
{
    rect.y = std::min(SCREEN_HEIGHT - rect.h, rect.y + PADDLE_SPEED);
}

void Paddle::move()
{
    // TODO: investigate whether AI should be implemented here so that the "cpu" controls it.
}

void Paddle::center()
{
    rect.y = SCREEN_HEIGHT / 2;
}

void Paddle::render()
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

const SDL_Rect &Paddle::getRect() const
{
    return rect;
}
