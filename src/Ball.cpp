#include "Ball.h"
#include "AudioManager.h"

Ball::Ball(int x, int y) : velX(BALL_VELOCITY), velY(BALL_VELOCITY)
{
    rect.x = x;
    rect.y = y;
    rect.w = 20; // tamaño de la pelota
    rect.h = 20;
}

void Ball::move()
{
    rect.x += velX;
    rect.y += velY;

    // Rebotar en las paredes superior e inferior
    if (rect.y <= 0 || rect.y + rect.h >= SCREEN_HEIGHT)
    {
        velY = -velY;
        Mix_PlayChannel(-1, sound_bounce, 0);  // Reproduce sonido de rebote
    }

    // Chequeo de punto anotado
    if (rect.x <= 0 || rect.x + rect.w >= SCREEN_WIDTH)
    {
        // Reinicia la posición de la pelota al centro
        rect.x = SCREEN_WIDTH / 2 - rect.w / 2;
        rect.y = SCREEN_HEIGHT / 2 - rect.h / 2;

        // Opcional: Ajusta velX para comenzar hacia el lado del jugador que no anotó
        velX = -velX; // Invierte dirección inicial como ejemplo
        
        Mix_PlayChannel(-1, sound_score, 0);  // Reproduce sonido de anotación
    }
}

bool Ball::detectCollision(const Paddle &paddle)
{
    SDL_Rect paddleRect = paddle.getRect();
    if (SDL_HasIntersection(&rect, &paddleRect))
    {
        velX = -velX; // Invierte la dirección X
        return true;
    }
    return false;
}

void Ball::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Color blanco
    SDL_RenderFillRect(renderer, &rect);
}
