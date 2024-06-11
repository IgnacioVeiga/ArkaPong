#include "Ball.h"
#include <cstdlib>
#include <ctime>
#include "../managers/TextureManager.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"

Ball::Ball() : velX(BALL_SPEED), velY(BALL_SPEED)
{
	rect = {
		SCREEN_WIDTH / 2 - (BALL_SIZE * scale) / 2,		// X
		SCREEN_HEIGHT / 2 - (BALL_SIZE * scale) / 2,	// Y
		BALL_SIZE * scale,								// W
		BALL_SIZE * scale								// H
	};
}

void Ball::move()
{
	//rect.x += velX;
	//rect.y += velY;
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
	TextureManager::drawTexture("vaus", rect.x, rect.y, &clip, SDL_FLIP_NONE, scale);
}

const SDL_Rect& Ball::getRect() const
{
	return rect;
}