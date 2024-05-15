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

public:
    MenuState();
    ~MenuState();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif
