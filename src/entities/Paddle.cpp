#include "Paddle.h"
#include "GameConstants.h"
#include <algorithm>

Paddle::Paddle(SDL_Renderer *renderer, int x) : renderer(renderer)
{
    // Cargar imagen BMP directamente
    const char *imagePath = "assets/sprites/paddle.bmp";
    SDL_Surface *tempSurface = SDL_LoadBMP(imagePath);
    if (!tempSurface)
    {
        SDL_Log("Unable to load BMP file: %s, SDL Error: %s", imagePath, SDL_GetError());
    }
    else
    {
        // Crear una textura a partir de la superficie
        texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        SDL_FreeSurface(tempSurface); // Liberar la superficie después de crear la textura
        if (!texture)
        {
            SDL_Log("Unable to create texture from %s, SDL Error: %s", imagePath, SDL_GetError());
        }
    }

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
    // Este método podría estar vacío si no necesitas un movimiento continuo
    // o puedes poner lógica para movimientos automáticos o basados en IA
}

void Paddle::render(SDL_Renderer *renderer)
{
    if (texture)
    {
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }
    else
    {
        // Dibujo de fallback si no se carga la textura
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanco
        SDL_RenderFillRect(renderer, &rect);
    }
}

const SDL_Rect &Paddle::getRect() const
{
    return rect;
}
