#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

#include "GameState.h"
#include "TextManager.h"

class PauseState : public GameState
{
private:
    SDL_Renderer *renderer;
    TextManager *textManager;

public:
    PauseState(SDL_Renderer *renderer);
    ~PauseState();

    void handleInput() override;
    void update() override;
    void render(SDL_Renderer *renderer) override;
};

#endif
