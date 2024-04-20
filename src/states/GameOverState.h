#ifndef GAME_OVER_STATE_H
#define GAME_OVER_STATE_H

#include "GameState.h"
#include "TextManager.h"

class GameOverState : public GameState
{
public:
    GameOverState(SDL_Renderer *renderer);
    ~GameOverState();
    void handleInput() override;
    void update() override;
    void render(SDL_Renderer *renderer) override;

private:
    SDL_Renderer *renderer;
    TextManager *textManager;
};

#endif
