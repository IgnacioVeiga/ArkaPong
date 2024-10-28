#pragma once

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Init() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Cleanup() = 0;
};
