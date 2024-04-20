#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "GameState.h"
#include "TextManager.h"
#include "AudioManager.h"
#include "GameFlowManager.h"

class MenuState : public GameState
{
private:
    SDL_Renderer *renderer;
    TextManager *textManager;
    AudioManager *audioManager;
    GameFlowManager *flowManager;

public:
    MenuState(SDL_Renderer *renderer, GameFlowManager *flowMgr);
    ~MenuState();

    void handleInput() override;
    void update() override;
    void render(SDL_Renderer *renderer) override;
};

#endif
