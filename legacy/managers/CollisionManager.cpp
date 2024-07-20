#include "CollisionManager.h"
#include <SDL2/SDL.h>
#include "../utilities/GameConstants.h"

CollisionManager::CollisionManager()
{
	audioManager = new AudioManager();
	audioManager->loadSound("paddle_bounce", "assets/audio/sfx/ball_hit_vaus.wav");
}

CollisionManager::~CollisionManager()
{
	delete audioManager;
}

bool CollisionManager::CheckWallCollisions(Ball &ball)
{
	SDL_Rect rect = ball.getRect();
	int velX, velY;
	ball.getVelocity(velX, velY);

	// Check collisions against the ceiling or floor
	if (CheckCollision(WALL_TOP, rect) || CheckCollision(WALL_BOTTOM, rect))
	{
		// Hit, so reverse velY
		ball.setVelocity(velX, -velY);
		return true;
	}
	return false;
}

bool CollisionManager::CheckPaddleCollision(Paddle &paddle, Ball &ball)
{
	SDL_Rect paddleRect = paddle.getRect();
	SDL_Rect ballRect = ball.getRect();

	CollisionSide side = DetectCollisionSide(ballRect, paddleRect);

	int velX, velY;
	ball.getVelocity(velX, velY);

	switch (side)
	{
	case CollisionSide::RIGHT:
	case CollisionSide::LEFT:
	{
		// Adjust the Y velocity based on the impact position
		int paddleCenter = paddleRect.y + paddleRect.h / 2;
		int ballCenter = ballRect.y + ballRect.h / 2;
		int deltaY = ballCenter - paddleCenter;
		velY += deltaY / 15;

		// Reverse the X velocity
		ball.setVelocity(-velX, velY);
		break;
	}
	case CollisionSide::TOP:
	case CollisionSide::BOTTOM:
	{
		// Invert the Y velocity if it hits the top or bottom
		ball.setVelocity(velX, -velY);
		break;
	}
	case CollisionSide::NONE:
	{
		// No collision
		return false;
	}
	}

	audioManager->playSound("paddle_bounce");
	return true;
}

CollisionSide CollisionManager::CheckBallOutOfBounds(Ball &ball)
{
	SDL_Rect ballRect = ball.getRect();
	if (ballRect.x + ballRect.w < 0)
	{
		return CollisionSide::LEFT;
	}
	else if (ballRect.x + ballRect.w > SCREEN_WIDTH)
	{
		return CollisionSide::RIGHT;
	}
	return CollisionSide::NONE;
}

bool CollisionManager::CheckCollision(const SDL_Rect &rect1, const SDL_Rect &rect2)
{
	// Simple AABB collision detection
	return (rect1.x < rect2.x + rect2.w &&
			rect1.x + rect1.w > rect2.x &&
			rect1.y < rect2.y + rect2.h &&
			rect1.y + rect1.h > rect2.y);
}

CollisionSide CollisionManager::DetectCollisionSide(const SDL_Rect &ballRect, const SDL_Rect &paddleRect)
{
	// Define the sides of the paddle
	int left = paddleRect.x;
	int right = paddleRect.x + paddleRect.w;
	int top = paddleRect.y;
	int bottom = paddleRect.y + paddleRect.h;

	// Determine the side of the collision
	if (ballRect.x + ballRect.w < left)
	{
		return CollisionSide::NONE; // No collision
	}
	if (ballRect.x > right)
	{
		return CollisionSide::NONE; // No collision
	}
	if (ballRect.y + ballRect.h < top)
	{
		return CollisionSide::NONE; // No collision
	}
	if (ballRect.y > bottom)
	{
		return CollisionSide::NONE; // No collision
	}

	// Determine if the collision is on the front, back, top or bottom
	int ballCenterX = ballRect.x + ballRect.w / 2;
	int ballCenterY = ballRect.y + ballRect.h / 2;
	int paddleCenterX = paddleRect.x + paddleRect.w / 2;
	int paddleCenterY = paddleRect.y + paddleRect.h / 2;

	if (ballCenterX < paddleCenterX)
	{
		return CollisionSide::RIGHT;
	}
	if (ballCenterX > paddleCenterX)
	{
		return CollisionSide::LEFT;
	}
	if (ballCenterY < paddleCenterY)
	{
		return CollisionSide::TOP;
	}
	return CollisionSide::BOTTOM;
}