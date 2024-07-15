#include "SceneManager.h"
#include <iostream>

SceneManager::SceneManager(GameScene* newScene) {
    currentScene = newScene;
}

SceneManager::~SceneManager()
{
    if (currentScene)
    {
        delete currentScene;
    }
}

void SceneManager::changeScene(GameScene *newScene)
{
    if (currentScene)
    {
        delete currentScene;
    }
    currentScene = newScene;
}

void SceneManager::handleInput()
{
    if (currentScene)
    {
        currentScene->handleInput();
    }
}

void SceneManager::update()
{
    if (currentScene)
    {
        currentScene->update();
    }
}

void SceneManager::render()
{
    if (currentScene)
    {
        currentScene->render();
    }
}
