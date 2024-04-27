#include "GameOverState.h"
#include "GameConstants.h"
#include <Game.h>

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
    // Gestionar la entrada para salir al MenuState o del juego
}

void GameOverState::update()
{
    // Actualización específica para el estado Game Over, si es necesario
}

void GameOverState::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255); // Fondo negro
    SDL_RenderClear(Game::renderer);
    textManager->renderText("Game Over", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(Game::renderer);
}
