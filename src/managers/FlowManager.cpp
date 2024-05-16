#include "FlowManager.h"
#include <iostream>

FlowManager::~FlowManager()
{
    if (currentState)
    {
        delete currentState;
    }
}

void FlowManager::changeState(GameState *newState)
{
    if (currentState)
    {
        delete currentState;
    }
    currentState = newState;
}

void FlowManager::handleInput()
{
    if (currentState)
    {
        currentState->handleInput();
    }
}

void FlowManager::update()
{
    if (currentState)
    {
        currentState->update();
    }
}

void FlowManager::render()
{
    if (currentState)
    {
        currentState->render();
    }
}
