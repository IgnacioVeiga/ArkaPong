#pragma once

#include <array>
#include <cassert>
#include <queue>
#include "Core/CoreExport.h"
#include "Core/Entity/Entity.h"

class CORE_API EntityManager {
public:
    EntityManager();

    Entity CreateEntity();

    void DestroyEntity(const Entity entity);

    void SetSignature(const Entity entity, const Signature signature);

    Signature GetSignature(const Entity entity) const;

    std::vector<Entity> GetAllEntities() const;

    bool EntityExists(Entity entity) const;
private:
    // Queue of unused entity IDs
    std::queue<Entity> mAvailableEntities{};

    // Array of signatures where the index corresponds to the entity ID
    std::array<Signature, MAX_ENTITIES> mSignatures{};

    // Total living entities - used to keep limits on how many exist
    uint32_t mLivingEntityCount{};
};
