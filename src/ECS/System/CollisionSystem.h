#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../../Utils/SpatialHash.h"
#include "../Coordinator.h"
#include "../Component/CollisionComponent.h"
#include "../Component/PositionComponent.h"

class CollisionSystem : public System
{
public:
    void Init()
    {
        Signature signature;
        signature.set(Game::coordinator.GetComponentType<CollisionComponent>());
        Game::coordinator.SetSystemSignature<CollisionSystem>(signature);
    }

    void Update(float deltaTime)
    {
        spatialHash.Clear();
        for (auto const &entity : mEntities)
        {
            CollisionComponent &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
            PositionComponent &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

            collisionComponent.collider.x = static_cast<int>(positionComponent.x);
            collisionComponent.collider.y = static_cast<int>(positionComponent.y);

            spatialHash.Insert(entity, collisionComponent.collider);
        }

        for (auto const &entity : mEntities)
        {
            CollisionComponent &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
            PositionComponent &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

            collisionComponent.collider.x = static_cast<int>(positionComponent.x);
            collisionComponent.collider.y = static_cast<int>(positionComponent.y);

            std::vector<Entity> possibleCollisions = spatialHash.Retrieve(collisionComponent.collider);

            for (auto const &otherEntity : possibleCollisions)
            {
                if (entity != otherEntity && CheckCollision(
                                                 positionComponent,
                                                 collisionComponent,
                                                 Game::coordinator.GetComponent<PositionComponent>(otherEntity),
                                                 Game::coordinator.GetComponent<CollisionComponent>(otherEntity)))
                {
                    HandleCollision(entity, otherEntity);
                }
            }
        }
    }

private:
    bool CheckCollision(PositionComponent &posA, CollisionComponent &colA, PositionComponent &posB, CollisionComponent &colB)
    {
        SDL_Rect rectA = {static_cast<int>(posA.x + colA.collider.x), static_cast<int>(posA.y + colA.collider.y), colA.collider.w, colA.collider.h};
        SDL_Rect rectB = {static_cast<int>(posB.x + colB.collider.x), static_cast<int>(posB.y + colB.collider.y), colB.collider.w, colB.collider.h};

        return SDL_HasIntersection(&rectA, &rectB);
    }

    void HandleCollision(Entity entityA, Entity entityB)
    {
        // Placeholder for collision handling logic, example:
        Bounce(entityA, entityB);
    }

    void Bounce(Entity entityA, Entity entityB)
    {
        auto &velA = Game::coordinator.GetComponent<VelocityComponent>(entityA);
        auto &posA = Game::coordinator.GetComponent<PositionComponent>(entityA);
        auto &colA = Game::coordinator.GetComponent<CollisionComponent>(entityA);

        auto &posB = Game::coordinator.GetComponent<PositionComponent>(entityB);
        auto &colB = Game::coordinator.GetComponent<CollisionComponent>(entityB);

        // Calculate overlap on each side of the collision
        float overlapLeft = (posA.x + colA.collider.x + colA.collider.w) - (posB.x + colB.collider.x);
        float overlapRight = (posB.x + colB.collider.x + colB.collider.w) - (posA.x + colA.collider.x);
        float overlapTop = (posA.y + colA.collider.y + colA.collider.h) - (posB.y + colB.collider.y);
        float overlapBottom = (posB.y + colB.collider.y + colB.collider.h) - (posA.y + colA.collider.y);

        // Determine which side the collision is coming from
        bool fromLeft = fabs(overlapLeft) < fabs(overlapRight);
        bool fromTop = fabs(overlapTop) < fabs(overlapBottom);

        // Find the minimum overlap in the X and Y axes
        float minOverlapX = fromLeft ? overlapLeft : overlapRight;
        float minOverlapY = fromTop ? overlapTop : overlapBottom;

        // Determine whether the collision is horizontal or vertical
        if (fabs(minOverlapX) < fabs(minOverlapY))
        {
            // Horizontal collision
            velA.x = -velA.x;
            colA.collisionSide = fromLeft ? CollisionSide::LEFT : CollisionSide::RIGHT;
        }
        else
        {
            // Vertical collision
            velA.y = -velA.y;
            colA.collisionSide = fromTop ? CollisionSide::TOP : CollisionSide::BOTTOM;
        }
    }

    SpatialHash spatialHash;
};
