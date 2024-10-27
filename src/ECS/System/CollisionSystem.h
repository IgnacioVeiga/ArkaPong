#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "../../Game.h"
#include "../../Utils/SpatialHash.h"
#include "../Coordinator.h"
#include "../Component/CollisionComponent.h"
#include "../Component/TransformComponent.h"

class CollisionSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<CollisionComponent>());
		signature.set(Game::coordinator.GetComponentType<TransformComponent>());
		Game::coordinator.SetSystemSignature<CollisionSystem>(signature);
	}

	void Update()
	{
		spatialHash.Clear();
		PopulateSpatialHash();

		// List
		std::vector<std::pair<Entity, Entity>> collisions;
		DetectCollisions(collisions);

		// Resolve
		for (const auto &pair : collisions)
		{
			ResolveCollision(pair.first, pair.second);
		}
	}

private:
	void PopulateSpatialHash()
	{
		for (const auto &entity : mEntities)
		{
			auto &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
			auto &transformComponent = Game::coordinator.GetComponent<TransformComponent>(entity);

			UpdateColliderPosition(collisionComponent, transformComponent);
			spatialHash.Insert(entity, collisionComponent.collider);
		}
	}

	void UpdateColliderPosition(CollisionComponent &collisionComponent, TransformComponent &transformComponent)
	{
		collisionComponent.collider.x = static_cast<int>(transformComponent.position.x);
		collisionComponent.collider.y = static_cast<int>(transformComponent.position.y);
	}

	void DetectCollisions(std::vector<std::pair<Entity, Entity>> &collisions)
	{
		for (const auto &entity : mEntities)
		{
			auto &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
			std::vector<Entity> possibleCollisions = spatialHash.Retrieve(collisionComponent.collider);

			for (const auto &otherEntity : possibleCollisions)
			{
				if (entity == otherEntity || entity >= otherEntity)
					continue;

				if (CheckCollision(entity, otherEntity))
				{
					collisions.emplace_back(entity, otherEntity);
				}
			}
		}
	}

	bool CheckCollision(Entity entityA, Entity entityB)
	{
		auto &colliderA = Game::coordinator.GetComponent<CollisionComponent>(entityA).collider;
		auto &colliderB = Game::coordinator.GetComponent<CollisionComponent>(entityB).collider;

		return SDL_HasIntersection(&colliderA, &colliderB);
	}

	void ResolveCollision(Entity entityA, Entity entityB)
	{
		auto &colA = Game::coordinator.GetComponent<CollisionComponent>(entityA);
		auto &colB = Game::coordinator.GetComponent<CollisionComponent>(entityB);

		if (colA.onCollision)
			colA.onCollision(entityA, entityB);
		if (colB.onCollision)
			colB.onCollision(entityB, entityA);
	}

	SpatialHash spatialHash;
};
