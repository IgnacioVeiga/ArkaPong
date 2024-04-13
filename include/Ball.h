#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include "GameConstants.h"

class Ball
{
public:
    Ball(int x, int y);
    void move();
    bool detectCollision(const Paddle &paddle);
    void render(SDL_Renderer *renderer);

private:
    SDL_Rect rect;
    int velX, velY;
};

#endif // BALL_H
