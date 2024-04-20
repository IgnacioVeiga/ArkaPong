#include "GameFlowManager.h"
#include <iostream>

GameFlowManager::~GameFlowManager()
{
    if (currentState)
    {
        delete currentState;
    }
}

void GameFlowManager::changeState(GameState *newState)
{
    if (currentState)
    {
        delete currentState;
    }
    currentState = newState;
}

void GameFlowManager::handleInput()
{
    if (currentState)
    {
        currentState->handleInput();
    }
}

void GameFlowManager::update()
{
    if (currentState)
    {
        currentState->update();
    }
}

void GameFlowManager::render(SDL_Renderer *renderer)
{
    if (currentState)
    {
        currentState->render(renderer);
    }
}
