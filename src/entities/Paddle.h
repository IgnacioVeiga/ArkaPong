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
    SDL_Rect clip = {0, 0, 32, 8};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_Point rotation_point = {0, 7};
    double rotation_angle = 90.0;

    void moveUp();
    void moveDown();
    void move() override;
    void center() override;
    void render() override;
    const SDL_Rect &getRect() const override;
};

#endif
