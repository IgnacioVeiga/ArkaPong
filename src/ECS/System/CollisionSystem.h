#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "../../Game.h"
#include "../../Utils/SpatialHash.h"
#include "../Coordinator.h"
#include "../Component/CollisionComponent.h"
#include "../Component/PositionComponent.h"
#include "../Component/VelocityComponent.h"

class CollisionSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<CollisionComponent>());
		signature.set(Game::coordinator.GetComponentType<PositionComponent>());
		Game::coordinator.SetSystemSignature<CollisionSystem>(signature);
	}

	void Update(float deltaTime)
	{
		spatialHash.Clear();
		PopulateSpatialHash();

		for (const auto &entity : mEntities)
		{
			auto &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
			auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

			std::vector<Entity> possibleCollisions = spatialHash.Retrieve(collisionComponent.collider);

			for (const auto &otherEntity : possibleCollisions)
			{
				auto &otherCollisionComponent = Game::coordinator.GetComponent<CollisionComponent>(otherEntity).collider;

				if (entity != otherEntity && entity < otherEntity && SDL_HasIntersection(&collisionComponent.collider, &otherCollisionComponent))
				{
					ResolveCollision(entity, otherEntity);
				}
			}
		}
	}

private:
	void PopulateSpatialHash()
	{
		for (const auto &entity : mEntities)
		{
			auto &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
			auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

			// Update collider position in case position changes during movement
			collisionComponent.collider.x = static_cast<int>(positionComponent.x);
			collisionComponent.collider.y = static_cast<int>(positionComponent.y);

			spatialHash.Insert(entity, collisionComponent.collider);
		}
	}

	void ResolveCollision(Entity entityA, Entity entityB)
	{
		auto &colA = Game::coordinator.GetComponent<CollisionComponent>(entityA);
		auto &colB = Game::coordinator.GetComponent<CollisionComponent>(entityB);

		if (colA.onCollision)
		{
			colA.onCollision(entityA, entityB);
		}
		if (colB.onCollision)
		{
			colB.onCollision(entityB, entityA);
		}
	}

	SpatialHash spatialHash;
};
