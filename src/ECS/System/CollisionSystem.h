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
            auto &collider = Game::coordinator.GetComponent<CollisionComponent>(entity);
            auto &position = Game::coordinator.GetComponent<PositionComponent>(entity);

            SDL_Rect rect = {
                static_cast<int>(position.x), // X
                static_cast<int>(position.y), // Y
                collider.collider.w,          // W
                collider.collider.h           // H
            };
            spatialHash.Insert(entity, rect);
        }

        for (auto const &entity : mEntities)
        {
            auto &collider = Game::coordinator.GetComponent<CollisionComponent>(entity);
            auto &position = Game::coordinator.GetComponent<PositionComponent>(entity);

            SDL_Rect rect = {
                static_cast<int>(position.x), // X
                static_cast<int>(position.y), // Y
                collider.collider.w,          // W
                collider.collider.h           // H
            };
            auto possibleCollisions = spatialHash.Retrieve(rect);

            for (auto const &otherEntity : possibleCollisions)
            {
                if (entity != otherEntity && CheckCollision(
                                                 position,
                                                 collider,
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
        SDL_Rect rectA = {static_cast<int>(posA.x), static_cast<int>(posA.y), colA.collider.w, colA.collider.h};
        SDL_Rect rectB = {static_cast<int>(posB.x), static_cast<int>(posB.y), colB.collider.w, colB.collider.h};

        return SDL_HasIntersection(&rectA, &rectB);
    }

    void HandleCollision(Entity entityA, Entity entityB)
    {
        auto &colliderA = Game::coordinator.GetComponent<CollisionComponent>(entityA);
        auto &colliderB = Game::coordinator.GetComponent<CollisionComponent>(entityB);

        for (auto &reaction : colliderA.reactions)
        {
            reaction.reaction(entityA, entityB);
        }

        for (auto &reaction : colliderB.reactions)
        {
            reaction.reaction(entityB, entityA);
        }
    }

    SpatialHash spatialHash;
};
