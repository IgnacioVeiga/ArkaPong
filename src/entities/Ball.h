#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Paddle.h"

class Ball : public Entity
{
public:
    Ball(SDL_Renderer *renderer, const char *imagePath, int x, int y, int w, int h);
    ~Ball();
    void move() override;
    void reset(int x, int y);
    void render(SDL_Renderer *renderer) override;
    const SDL_Rect &getRect() const override;

    void getVelocity(int &velX, int &velY) const
    {
        velX = this->velX;
        velY = this->velY;
    }
    void setVelocity(int velX, int velY)
    {
        this->velX = velX;
        this->velY = velY;
    }

private:
    SDL_Renderer *renderer;
    int velX, velY;
    void setInitialDirection();
};

#endif
