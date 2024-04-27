#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <SDL2/SDL.h>

class GameState
{
public:
    virtual ~GameState() {}
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif
