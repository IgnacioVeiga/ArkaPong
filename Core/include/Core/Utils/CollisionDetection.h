#pragma once

#include <vector>
#include "Core/Entity/Entity.h"
#include "Vec2.h"

class CollisionDetection {
public:
    virtual ~CollisionDetection() = default;

    virtual void Clear() = 0;

    virtual void Insert(Entity entity, Vec2 position, SDL_FRect collider) = 0;

    // virtual void GetPotentialCollisions(std::vector<std::pair<Entity, Entity>> &collisions) = 0;
    virtual std::vector<Entity> Retrieve(const SDL_FRect &collider) = 0;
};
