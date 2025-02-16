#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include "../Scene.h"

class SceneManager
{
public:
    void Add(const std::string& name, std::unique_ptr<Scene> scene)
    {
        scenes[name] = std::move(scene);
    }

    // Initiate multiple scenes
    void Init(const std::string& name)
    {
        if (scenes.find(name) != scenes.end())
        {
            Scene* newScene = scenes[name].get();
            newScene->Init();
            activeScenes.push_back(newScene);
        }
    }

    // Update all active scenes
    void Update(float delta_time)
    {   
        for (auto& scene : activeScenes)
        {
            scene->Update(delta_time);
        }
    }

    // Switch to a new scene, replacing all the current ones.
    void ChangeScene(const std::string& name)
    {
        CleanupActiveScenes();
        Init(name);
    }

    // Add a new scene without removing the previous ones
    void PushScene(const std::string& name)
    {
        if (scenes.find(name) != scenes.end())
        {
            Scene* newScene = scenes[name].get();
            newScene->Init();
            activeScenes.push_back(newScene);
        }
    }

    // Remove last scene
    void PopScene()
    {
        if (!activeScenes.empty())
        {
            Scene* scene = activeScenes.back();
            scene->Cleanup();
            activeScenes.pop_back();
        }
    }

    // Remove a scene by name
    void RemoveScene(const std::string& name)
    {
        scenes.erase(name);
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    std::vector<Scene*> activeScenes;

    void CleanupActiveScenes()
    {
        for (auto& scene : activeScenes)
        {
            scene->Cleanup();
        }
        activeScenes.clear();
    }
};
