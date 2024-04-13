#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
#include "GameConstants.h"

class Paddle
{
public:
    Paddle(int x, int y);
    void moveUp();
    void moveDown();
    void render(SDL_Renderer *renderer);
    SDL_Rect getRect() const;

private:
    SDL_Rect rect;
};

#endif // PADDLE_H
