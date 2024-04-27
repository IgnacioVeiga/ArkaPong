#include "Paddle.h"
#include "TextureManager.h"
#include "GameConstants.h"
#include <algorithm>
#include <Game.h>

Paddle::Paddle(int x)
{
    texture = TextureManager::LoadTexture("assets/sprites/paddle.bmp");

    // Definir el rectángulo para el rendering de la textura
    rect = {
        x,                                     // X
        SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, // Y
        PADDLE_WIDTH,                          // W
        PADDLE_HEIGHT                          // H
    };
}

Paddle::~Paddle()
{
    SDL_DestroyTexture(texture);
}

void Paddle::moveUp()
{
    rect.y = std::max(0, rect.y - PADDLE_SPEED);
}

void Paddle::moveDown()
{
    rect.y = std::min(SCREEN_HEIGHT - rect.h, rect.y + PADDLE_SPEED);
}

void Paddle::move()
{
    // TODO: revisar si se deberia implementar la IA acá
}

void Paddle::center()
{
    rect.x = SCREEN_WIDTH / 2;
    rect.y = SCREEN_HEIGHT / 2;
}

void Paddle::render()
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

const SDL_Rect &Paddle::getRect() const
{
    return rect;
}
