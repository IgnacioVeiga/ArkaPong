#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "GameState.h"
#include "../managers/TextManager.h"

class PauseState : public GameState
{
private:
    TextManager *textManager;

public:
    PauseState();
    ~PauseState();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif
