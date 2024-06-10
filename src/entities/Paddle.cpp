#include "Paddle.h"
#include <algorithm>
#include "../managers/TextureManager.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"

Paddle::Paddle(PlayerSide side) : side(side)
{
    int x = (side == PlayerSide::PLAYER_LEFT) ? PADDLE_OFFSET : SCREEN_WIDTH - PADDLE_OFFSET;
    // Rectangle used for the position and the colider
    rect = {
        x,                                     // X
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, // Y
        PADDLE_WIDTH,                          // W
        PADDLE_HEIGHT                          // H
    };
}

void Paddle::moveUp()
{
    rect.y = std::max(0, rect.y - PADDLE_SPEED);
}

void Paddle::moveDown()
{
    rect.y = std::min(SCREEN_HEIGHT - PADDLE_HEIGHT, rect.y + PADDLE_SPEED);
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
    if (side == PlayerSide::PLAYER_RIGHT)
    {
        // The texture first flips and then rotates.
        flip = SDL_FLIP_VERTICAL;
    }

    // FOR DEBUG REASONS, this is the real colider. REMOVE LATER.
    // SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    // SDL_RenderFillRect(Game::renderer, &rect);

    TextureManager::drawTexture("paddle", rect.x, rect.y, &clip, rotation_angle, &rotation_point, flip);
}

const SDL_Rect &Paddle::getRect() const
{
    return rect;
}
