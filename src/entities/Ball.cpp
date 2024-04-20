#include "Ball.h"
#include "GameConstants.h"
#include <cstdlib>
#include <ctime>

Ball::Ball(SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h) : renderer(renderer), velX(BALL_SPEED), velY(BALL_SPEED)
{
    this->renderer = renderer;

    // Cargar imagen BMP directamente
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
    rect = {x, y, w, h};
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

void Ball::reset(int x, int y)
{
    rect.x = x;
    rect.y = y;
    setInitialDirection();
}

void Ball::setInitialDirection()
{
    velX = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
    int factor = rand() % BALL_SPEED + 1; // Asegura que el factor no sea cero
    velY = (rand() % 2 == 0 ? -factor : factor);
}

void Ball::render(SDL_Renderer *renderer)
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

const SDL_Rect &Ball::getRect() const
{
    return rect;
}