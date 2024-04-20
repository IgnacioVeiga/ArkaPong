#include "PauseState.h"

PauseState::PauseState(SDL_Renderer *rend) : renderer(rend)
{
    textManager = new TextManager(renderer);
}

PauseState::~PauseState()
{
    delete textManager;
}

void PauseState::handleInput()
{
    // TODO: permitir cambiar a PlayState o MenuState
}

void PauseState::update()
{
    // Puede que no necesite actualizar nada específico
}

void PauseState::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    textManager->renderText("Game Paused - Press SPACE to continue", 100, 100);
    SDL_RenderPresent(renderer);
}
