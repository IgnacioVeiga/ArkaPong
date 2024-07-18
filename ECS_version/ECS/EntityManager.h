#pragma once
#include <queue>
#include <array>
#include "Entity.h"
#include <stdexcept>

class EntityManager
{
public:
    EntityManager()
    {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            availableEntities.push(entity);
        }
    }

    Entity CreateEntity()
    {
        if (livingEntityCount >= MAX_ENTITIES)
        {
            throw std::runtime_error("Too many entities in existence.");
        }
        Entity id = availableEntities.front();
        availableEntities.pop();
        ++livingEntityCount;
        return id;
    }

    void DestroyEntity(Entity entity)
    {
        if (entity >= MAX_ENTITIES)
        {
            throw std::runtime_error("Entity out of range.");
        }
        signatures[entity].reset();
        availableEntities.push(entity);
        --livingEntityCount;
    }

    void SetSignature(Entity entity, Signature signature)
    {
        if (entity >= MAX_ENTITIES)
        {
            throw std::runtime_error("Entity out of range.");
        }
        signatures[entity] = signature;
    }

    Signature GetSignature(Entity entity)
    {
        if (entity >= MAX_ENTITIES)
        {
            throw std::runtime_error("Entity out of range.");
        }
        return signatures[entity];
    }

private:
    std::queue<Entity> availableEntities{};
    std::array<Signature, MAX_ENTITIES> signatures{};
    std::uint32_t livingEntityCount{};
};
