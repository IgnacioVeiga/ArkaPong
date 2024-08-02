#pragma once

#include "../ECS/Coordinator.h"
#include <string>

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Cleanup() = 0; // New method to clean up the scene
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual bool SaveState(const std::string &filepath) = 0;
    virtual bool LoadState(const std::string &filepath) = 0;

protected:
    std::unordered_map<std::string, Entity> sceneEntities;
};
