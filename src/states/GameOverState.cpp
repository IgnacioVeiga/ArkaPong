#include "GameOverState.h"
#include "GameConstants.h"

GameOverState::GameOverState(SDL_Renderer *renderer) : renderer(renderer)
{
    textManager = new TextManager(renderer);
}

GameOverState::~GameOverState()
{
    delete textManager;
}

void GameOverState::handleInput()
{
    // Aquí puedes gestionar la entrada para reiniciar el juego o salir
}

void GameOverState::update()
{
    // Actualización específica para el estado Game Over, si es necesario
}

void GameOverState::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
    SDL_RenderClear(renderer);
    textManager->renderText("Game Over", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(renderer);
}
