#pragma once

#include "../ECS/Coordinator.h"

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;

protected:
    Coordinator *coordinator;
};
