#include "SceneManager.h"

void SceneManager::LoadScene(Scene *scene)
{
    currentScene = scene;
    currentScene->Load();
}

void SceneManager::Update(float deltaTime)
{
    if (currentScene)
    {
        currentScene->Update(deltaTime);
    }
}

void SceneManager::Render(SDL_Renderer *renderer)
{
    if (currentScene)
    {
        currentScene->Render(renderer);
    }
}
