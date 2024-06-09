#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.h"

class Paddle : public Entity
{
public:
    Paddle(int x);
    ~Paddle();
    void moveUp();
    void moveDown();
    void move() override;
    void center() override;
    void render() override;
    const SDL_Rect& getRect() const override;
};

#endif
