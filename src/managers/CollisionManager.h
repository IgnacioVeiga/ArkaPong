#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "ScoreManager.h"
#include "AudioManager.h"
#include "../entities/Ball.h"
#include "../utilities/GameConstants.h"

enum class CollisionSide {
    NONE,
    RIGHT,
    TOP,
    BOTTOM,
    LEFT
};

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();
	bool CheckWallCollisions(Ball& ball);
	bool CheckPaddleCollision(Paddle& paddle, Ball& ball);
	CollisionSide CheckBallOutOfBounds(Ball& ball);

private:
	SDL_Rect WALL_TOP = { 0, 0, SCREEN_WIDTH, 8 * SCALE };
	SDL_Rect WALL_BOTTOM = { 0, SCREEN_HEIGHT - 8 * SCALE, SCREEN_WIDTH, SCREEN_HEIGHT };

	bool CheckCollision(const SDL_Rect& rect1, const SDL_Rect& rect2);
	CollisionSide DetectCollisionSide(const SDL_Rect& ballRect, const SDL_Rect& paddleRect);

	AudioManager* audioManager;
};

#endif
