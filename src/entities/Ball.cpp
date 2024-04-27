#include "Ball.h"
#include "TextureManager.h"
#include "GameConstants.h"
#include <cstdlib>
#include <ctime>
#include <Game.h>

Ball::Ball() : velX(BALL_SPEED), velY(BALL_SPEED)
{
    texture = TextureManager::LoadTexture("assets/sprites/ball.bmp");

    // Definir el rectángulo para el rendering de la textura
    rect = {
        SCREEN_WIDTH / 2 - BALL_SIZE / 2,  // X
        SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // Y
        BALL_SIZE,                         // W
        BALL_SIZE                          // H
    };
}

Ball::~Ball()
{
    SDL_DestroyTexture(texture);
}

void Ball::move()
{
    rect.x += velX;
    rect.y += velY;
}

void Ball::center()
{
    rect.x = SCREEN_WIDTH / 2;
    rect.y = SCREEN_HEIGHT / 2;

    // Hacia izquierda o derecha (aleatorio)
    velX = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);

    // La velocidad en el eje Y no es siempre la misma
    int factor = rand() % BALL_SPEED + 1;

    // Hacia arriba o abajo (aleatorio)
    velY = (rand() % 2 == 0 ? -factor : factor);
}

void Ball::render()
{
    if (texture)
    {
        SDL_RenderCopy(Game::renderer, texture, NULL, &rect);
    }
    else
    {
        // Dibujo de fallback si no se carga la textura
        SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255); // Blanco
        SDL_RenderFillRect(Game::renderer, &rect);
    }
}

const SDL_Rect &Ball::getRect() const
{
    return rect;
}