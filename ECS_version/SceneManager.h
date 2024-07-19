#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
    SceneManager() = default;

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

    void Update()
    {
        if (currentScene)
        {
            currentScene->Update();
        }
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene *currentScene = nullptr;
};
