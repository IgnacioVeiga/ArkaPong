#pragma once

#include "Entity.h"
#include "Components.h"

class MovementSystem
{
public:
    void update(ComponentManager &componentManager)
    {
        for (auto &entity : entities)
        {
            auto *position = componentManager.getComponent<PositionComponent>(entity.getId());
            auto *velocity = componentManager.getComponent<VelocityComponent>(entity.getId());
            auto *movement = componentManager.getComponent<MovementComponent>(entity.getId());

            if (position && velocity && movement)
            {
                position->y += velocity->y * movement->speed;
            }
        }
    }

    void addEntity(Entity entity)
    {
        entities.push_back(entity);
    }

private:
    std::vector<Entity> entities;
};
