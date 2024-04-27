#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Paddle.h"

class Ball : public Entity
{
public:
    Ball();
    ~Ball();
    void move() override;
    void center();
    void render() override;
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
    int velX, velY;
};

#endif
