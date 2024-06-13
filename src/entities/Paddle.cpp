#include "Paddle.h"
#include <algorithm>
#include "../managers/TextureManager.h"
#include "../Game.h"

Paddle::Paddle(PlayerSide side) : side(side)
{
	int x = (side == PlayerSide::PLAYER_RIGHT) ? SCREEN_WIDTH - PADDLE_OFFSET : PADDLE_OFFSET;
	rect = {
		x,									   // X
		SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, // Y
		PADDLE_WIDTH,						   // W
		PADDLE_HEIGHT						   // H
	};
}

void Paddle::moveUp()
{
	rect.y = std::max((8 * SCALE), rect.y - PADDLE_SPEED);
}

void Paddle::moveDown()
{
	rect.y = std::min(SCREEN_HEIGHT - (8 * SCALE) - rect.h, rect.y + PADDLE_SPEED);
}

void Paddle::move()
{
	// TODO: investigate whether AI should be implemented here so that the "cpu" controls it.
}

void Paddle::center()
{
	rect.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
}

void Paddle::render()
{
	if (side == PlayerSide::PLAYER_RIGHT)
	{
		flip = SDL_FLIP_HORIZONTAL;
	}

	TextureManager::drawTexture("vaus", rect.x, rect.y, &clip, flip);
}

const SDL_Rect &Paddle::getRect() const
{
	return rect;
}
