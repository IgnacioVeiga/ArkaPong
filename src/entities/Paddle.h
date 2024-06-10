#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.h"

enum class PlayerSide
{
    PLAYER_LEFT,
    PLAYER_RIGHT
};

class Paddle : public Entity
{
public:
    Paddle(PlayerSide side);
    PlayerSide side = PlayerSide::PLAYER_LEFT;
    SDL_Rect clip = {0, 0, 31, 7};
    void moveUp();
    void moveDown();
    void move() override;
    void center() override;
    void render() override;
    const SDL_Rect &getRect() const override;
};

#endif
