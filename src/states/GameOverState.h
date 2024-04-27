#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "GameState.h"
#include "TextManager.h"

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
};

#endif
