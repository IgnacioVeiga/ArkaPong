#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"
#include "TextManager.h"
#include "AudioManager.h"
#include "GameFlowManager.h"

class MenuState : public GameState
{
private:
    TextManager *textManager;
    AudioManager *audioManager;
    GameFlowManager *flowManager;

public:
    MenuState(GameFlowManager *flowMgr);
    ~MenuState();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif
