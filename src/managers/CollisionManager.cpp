#include "CollisionManager.h"
#include <SDL2/SDL.h>
#include "../utilities/GameConstants.h"

CollisionManager::CollisionManager(ScoreManager *scoreManager)
    : scoreManager(scoreManager)
{
    audioManager = new AudioManager();
    audioManager->loadSound("wall_bounce", "assets/audio/sfx/ball_hit_obstacle.wav");
    audioManager->loadSound("paddle_bounce", "assets/audio/sfx/ball_hit_vaus.wav");
    audioManager->loadSound("score", "assets/audio/sfx/vaus_explosion.wav");
}

CollisionManager::~CollisionManager()
{
    delete audioManager;
}

void CollisionManager::handlePaddleCollision(Ball &ball, const Paddle &paddle)
{
    const SDL_Rect &ballRect = ball.getRect();
    const SDL_Rect &paddleRect = paddle.getRect();

    if (SDL_HasIntersection(&ballRect, &paddleRect))
    {
        // Hit paddle, so reverse velX
        int velX, velY;
        ball.getVelocity(velX, velY);

        // velY is adjusted according to the relative position of the impact on the paddle
        int paddleCenter = paddleRect.y + paddleRect.h / 2;
        int ballCenter = ballRect.y + ballRect.h / 2;
        int deltaY = ballCenter - paddleCenter;

        // TODO: Check this factor if it needs to be changed.
        velY += deltaY / 15;
        ball.setVelocity(-velX, velY);
        audioManager->playSound("paddle_bounce");
    }
}

void CollisionManager::handleWallCollisions(Ball &ball)
{
    SDL_Rect rect = ball.getRect();
    int velX, velY;
    ball.getVelocity(velX, velY);

    // Check collisions against the ceiling or floor
    if (rect.y <= 0 && velY < 0)
    {
        // Hit ceiling, so reverse velY
        ball.setVelocity(velX, -velY);
        audioManager->playSound("wall_bounce");
    }
    else if (rect.y + rect.h >= SCREEN_HEIGHT && velY > 0)
    {
        // Hit floor, so reverse velY
        ball.setVelocity(velX, -velY);
        audioManager->playSound("wall_bounce");
    }

    // Collisions with the left and right walls are checked for score
    if (rect.x <= 0 || rect.x + rect.w >= SCREEN_WIDTH)
    {
        ball.center();
        SDL_Delay(500);
        audioManager->playSound("score");
        SDL_Delay(2000);
        // TODO: center paddles
        if (rect.x <= 0)
        {
            scoreManager->increaseScoreRight();
        }
        else if (rect.x + rect.w >= SCREEN_WIDTH)
        {
            scoreManager->increaseScoreLeft();
        }
    }
}
