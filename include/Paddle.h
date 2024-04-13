#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>

class Paddle
{
public:
    Paddle(SDL_Renderer *renderer, int x, int y, int w, int h);
    void moveUp();
    void moveDown();
    void render();
    const SDL_Rect &getRect() const;

private:
    SDL_Renderer *renderer;
    SDL_Rect rect;
};

#endif