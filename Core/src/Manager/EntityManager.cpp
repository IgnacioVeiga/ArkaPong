#include "Core/Manager/EntityManager.h"

EntityManager::EntityManager()
{
    // Initialize the queue with all possible entity IDs
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
    {
        mAvailableEntities.push(entity);
    }
}

Entity EntityManager::CreateEntity()
{
    assert(mLivingEntityCount < MAX_ENTITIES && "Too many entities in existence.");

    // Take an ID from the front of the queue
    const Entity id = mAvailableEntities.front();
    mAvailableEntities.pop();
    ++mLivingEntityCount;
    return id;
}

void EntityManager::DestroyEntity(const Entity entity)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Invalidate the destroyed entity's signature
    mSignatures[entity].reset();

    // Put the destroyed ID at the back of the queue
    mAvailableEntities.push(entity);
    --mLivingEntityCount;
}

void EntityManager::SetSignature(const Entity entity, const Signature signature)
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Put this entity's signature into the array
    mSignatures[entity] = signature;
}

Signature EntityManager::GetSignature(const Entity entity) const
{
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    // Get this entity's signature from the array
    return mSignatures[entity];
}

std::vector<Entity> EntityManager::GetAllEntities() const
{
    std::vector<Entity> entities;
    entities.reserve(MAX_ENTITIES);
    for (Entity e = 0; e < MAX_ENTITIES; ++e)
    {
        // If the entity is active (has any signature)
        if (mSignatures[e].any())
        {
            entities.push_back(e);
        }
    }
    return entities;
}

bool EntityManager::EntityExists(Entity entity) const
{
    // If the entity has a signature with at least one active bit, we consider it existing
    return entity < MAX_ENTITIES && mSignatures[entity].any();
}
