#ifndef FLOW_MANAGER_H
#define FLOW_MANAGER_H

#include "../states/GameState.h"

class FlowManager
{
private:
    GameState *currentState;

public:
    FlowManager(GameState* newState);
    ~FlowManager();

    void changeState(GameState *newState);
    void handleInput();
    void update();
    void render();
};

#endif
