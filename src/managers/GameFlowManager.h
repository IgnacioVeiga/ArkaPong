#ifndef GAME_FLOW_MANAGER_H
#define GAME_FLOW_MANAGER_H

#include "GameState.h"

class GameFlowManager
{
private:
    GameState *currentState;

public:
    GameFlowManager() : currentState(nullptr) {}
    ~GameFlowManager();

    void changeState(GameState *newState);
    void handleInput();
    void update();
    void render();
};

#endif
