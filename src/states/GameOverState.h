#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "GameState.h"
#include "../managers/TextManager.h"
#include "../managers/AudioManager.h"

class GameOverState : public GameState
{
public:
    GameOverState();
    ~GameOverState();
    void handleInput() override;
    void update() override;
    void render() override;

private:
    TextManager *textManager;
    AudioManager* audioManager;

    Uint32 countdownTimer;
    int countdown;
};

#endif
