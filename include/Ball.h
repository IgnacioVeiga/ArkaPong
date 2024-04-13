#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "Paddle.h"

class Ball
{
public:
    Ball(SDL_Renderer *renderer, int x, int y, int w, int h);
    void move();
    void reset(int x, int y);
    void changeDirection(Paddle &paddle);
    void render();
    const SDL_Rect &getRect() const { return rect; }
    bool checkCollision(const SDL_Rect& paddleRect);

private:
    SDL_Renderer *renderer;
    SDL_Rect rect;
    int velX, velY;
};

#endif