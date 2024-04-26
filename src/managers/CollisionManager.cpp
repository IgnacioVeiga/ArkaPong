#include "CollisionManager.h"
#include "GameConstants.h"
#include <SDL2/SDL.h>

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
        // Invertir la dirección horizontal de la pelota
        int velX, velY;
        ball.getVelocity(velX, velY);

        // Ajustar la dirección vertical según la posición relativa de impacto en el paddle
        int paddleCenter = paddleRect.y + paddleRect.h / 2;
        int ballCenter = ballRect.y + ballRect.h / 2;
        int deltaY = ballCenter - paddleCenter;
        
        // Este factor de ajuste puede variar según tus necesidades de jugabilidad
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

    // Comprobar colisiones con las paredes superior e inferior y ajustar la dirección vertical
    if (rect.y <= 0 && velY < 0)
    {
        // Toca la pared superior y se mueve hacia arriba
        ball.setVelocity(velX, -velY);
        audioManager->playSound("wall_bounce");
    }
    else if (rect.y + rect.h >= SCREEN_HEIGHT && velY > 0)
    {
        // Toca la pared inferior y se mueve hacia abajo
        ball.setVelocity(velX, -velY);
        audioManager->playSound("wall_bounce");
    }

    // Comprobar colisiones con las paredes izquierda y derecha para puntuación
    if (rect.x <= 0 || rect.x + rect.w >= SCREEN_WIDTH)
    {
        ball.center();
        SDL_Delay(500);
        audioManager->playSound("score");
        SDL_Delay(2000);
        // TODO: centrar jugadores
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
