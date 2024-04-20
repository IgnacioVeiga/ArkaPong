#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.h"

class Paddle : public Entity
{
public:
    Paddle(SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h);
    ~Paddle();
    void moveUp();
    void moveDown();
    void move() override;  // Implementación específica de Paddle
    void render(SDL_Renderer *renderer) override;
    const SDL_Rect &getRect() const override;

private:
    SDL_Renderer *renderer;
};

#endif
