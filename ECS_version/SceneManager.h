#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
    SceneManager() = default;

    void AddScene(const std::string &name, std::unique_ptr<Scene> scene)
    {
        scenes[name] = std::move(scene);
    }

    void LoadScene(const std::string &name)
    {
        currentScene = scenes[name].get();
        if (currentScene)
        {
            currentScene->Load();
        }
    }

    void Update(float deltaTime)
    {
        if (currentScene)
        {
            currentScene->Update(deltaTime);
        }
    }

    void Render(SDL_Renderer* renderer)
    {
        if (currentScene)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            currentScene->Render();
            SDL_RenderPresent(renderer);
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene *currentScene = nullptr;
};
