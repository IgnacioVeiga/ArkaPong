#pragma once

#include "Scene.h"
#include "ECS/SystemManager.h"

class GameScene : public Scene
{
public:
    GameScene();
    void Load() override;
    void Update(float deltaTime) override;
    void Render() override;

private:
    SystemManager systemManager;
};
