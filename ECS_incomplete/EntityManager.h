#pragma once

#include "Entity.h"

class EntityManager
{
public:
    Entity createEntity()
    {
        Entity::Id id = nextId++;
        entities.push_back(Entity(id));
        return entities.back();
    }

private:
    Entity::Id nextId = 0;
    std::vector<Entity> entities;
};
