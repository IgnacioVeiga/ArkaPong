#pragma once

#include <vector>
#include "ECS/EntityManager.h"
#include "ECS/ComponentManager.h"
#include "ECS/SystemManager.h"

class Level
{
public:
    void Load();
    void Update(float deltaTime);
    void Render();

private:
    EntityManager entityManager;
    ComponentManager componentManager;
    SystemManager systemManager;
    std::vector<Entity> entities;
};
