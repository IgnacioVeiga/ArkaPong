#include "FlowManager.h"
#include <iostream>

FlowManager::FlowManager(GameScene* newScene) {
    currentScene = newScene;
}

FlowManager::~FlowManager()
{
    if (currentScene)
    {
        delete currentScene;
    }
}

void FlowManager::changeScene(GameScene *newScene)
{
    if (currentScene)
    {
        delete currentScene;
    }
    currentScene = newScene;
}

void FlowManager::handleInput()
{
    if (currentScene)
    {
        currentScene->handleInput();
    }
}

void FlowManager::update()
{
    if (currentScene)
    {
        currentScene->update();
    }
}

void FlowManager::render()
{
    if (currentScene)
    {
        currentScene->render();
    }
}
