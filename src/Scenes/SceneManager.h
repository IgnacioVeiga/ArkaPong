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
        if (currentScene && !isPaused)
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

    void PauseScene()
    {
        isPaused = true;
    }

    void ResumeScene()
    {
        isPaused = false;
    }

    Scene *GetCurrentScene() const
    {
        return currentScene;
    }

    bool SaveScene(const std::string &name, const std::string &filepath)
    {
        if (scenes.find(name) != scenes.end())
        {
            return scenes[name]->SaveState(filepath);
        }
        return false;
    }

    bool LoadScene(const std::string &name, const std::string &filepath)
    {
        if (scenes.find(name) != scenes.end())
        {
            return scenes[name]->LoadState(filepath);
        }
        return false;
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene *currentScene = nullptr;
    bool isPaused = false;
};
