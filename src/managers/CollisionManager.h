#ifndef COLLISION_MANAGER_H
#define COLLISION_MANAGER_H

#include "ScoreManager.h"
#include "AudioManager.h"
#include "../entities/Ball.h"

class CollisionManager
{
public:
    CollisionManager(ScoreManager *scoreManager);
    ~CollisionManager();
    void handlePaddleCollision(Ball &ball, const Paddle &paddle);
    void handleWallCollisions(Ball &ball);

private:
    ScoreManager *scoreManager;
    AudioManager *audioManager;
};

#endif
