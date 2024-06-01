#include "GameOverState.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"

GameOverState::GameOverState()
{
    textManager = new TextManager();
}

GameOverState::~GameOverState()
{
    delete textManager;
}

void GameOverState::handleInput()
{
    // GameState.h implementation, may be unnecessary
}

void GameOverState::update()
{
    // TODO: countdown to go to MenuState
}

void GameOverState::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    textManager->renderText("Game Over", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(Game::renderer);
}
