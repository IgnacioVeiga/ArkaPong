#ifndef PADDLE_H
#define PADDLE_H

#include "Entity.h"
#include "../utilities/GameConstants.h"

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
    SDL_Rect clip = {
        0, // X coordinate of the bitmap file
        0, // Y coordinate of the bitmap file
        PADDLE_WIDTH,
        PADDLE_HEIGHT};
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    void moveUp();
    void moveDown();
    void center();
    void render() override;
    const SDL_Rect &getRect() const override;
};

#endif
