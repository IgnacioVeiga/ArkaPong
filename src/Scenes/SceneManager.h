#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
    void Add(const std::string &name, std::unique_ptr<Scene> scene)
    {
        scenes[name] = std::move(scene);
    }

    void Init(const std::string &name)
    {
        currentScene = scenes[name].get();
        if (currentScene)
        {
            currentScene->Init();
        }
    }

    void Update(float deltaTime)
    {
        if (currentScene)
        {
            currentScene->Update(deltaTime);
        }
    }

    void ChangeScene(const std::string &name)
    {
        if (currentScene)
        {
            currentScene->Cleanup();
        }

        if (scenes.find(name) != scenes.end())
        {
            currentScene = scenes[name].get();
            if (currentScene)
            {
                currentScene->Init();
            }
        }
    }

    void RemoveScene(const std::string &name)
    {
        if (scenes.find(name) != scenes.end())
        {
            scenes.erase(name);
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene *currentScene = nullptr;
};
