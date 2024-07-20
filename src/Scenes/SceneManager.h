#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "Scene.h"

class SceneManager
{
public:
    SceneManager(Coordinator *coordinator) : coordinator(coordinator) {}

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

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene *currentScene = nullptr;
    Coordinator *coordinator;
};
