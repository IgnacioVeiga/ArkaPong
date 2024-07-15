#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <SDL2/SDL.h>

class GameScene
{
public:
    virtual ~GameScene() {}
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif
