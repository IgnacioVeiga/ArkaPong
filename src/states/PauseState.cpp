#include "PauseState.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"

PauseState::PauseState()
{
    textManager = new TextManager();
}

PauseState::~PauseState()
{
    delete textManager;
}

void PauseState::handleInput()
{
    // TODO: return to PlayState or MenuState
}

void PauseState::update()
{
    // GameState.h implementation, may be unnecessary
}

void PauseState::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    textManager->renderText("Game Paused", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TextAlignment::CENTER);
    textManager->renderText("Press SPACE to continue", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 30, TextAlignment::CENTER);
    textManager->renderText("ESC to quit", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 60, TextAlignment::CENTER);
    SDL_RenderPresent(Game::renderer);
}
