#pragma once

#include <SDL2/SDL.h>
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
		signature.set(Game::coordinator.GetComponentType<VelocityComponent>());
		Game::coordinator.SetSystemSignature<CollisionSystem>(signature);
	}

	void Update(float deltaTime)
	{
		spatialHash.Clear();
		PopulateSpatialHash();

		for (const auto &entity : mEntities)
		{
			CheckEntityCollisions(entity);
		}

		// TODO: test collision
	}

private:
	void PopulateSpatialHash()
	{
		for (const auto &entity : mEntities)
		{
			auto &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
			auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

			UpdateColliderPosition(positionComponent, collisionComponent);
			spatialHash.Insert(entity, collisionComponent.collider);
		}
	}

	void UpdateColliderPosition(PositionComponent &position, CollisionComponent &collision)
	{
		collision.collider.x = static_cast<int>(position.x);
		collision.collider.y = static_cast<int>(position.y);
	}

	void CheckEntityCollisions(Entity entity)
	{
		auto &collisionComponent = Game::coordinator.GetComponent<CollisionComponent>(entity);
		auto &positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

		std::vector<Entity> possibleCollisions = spatialHash.Retrieve(collisionComponent.collider);

		for (const auto &otherEntity : possibleCollisions)
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

	bool CheckCollision(const PositionComponent &posA, const CollisionComponent &colA, const PositionComponent &posB, const CollisionComponent &colB)
	{
		SDL_Rect rectA = {static_cast<int>(posA.x), static_cast<int>(posA.y), colA.collider.w, colA.collider.h};
		SDL_Rect rectB = {static_cast<int>(posB.x), static_cast<int>(posB.y), colB.collider.w, colB.collider.h};

		return SDL_HasIntersection(&rectA, &rectB);
	}

	void HandleCollision(Entity entityA, Entity entityB)
	{
		// Placeholder for collision handling logic, example:
		Bounce(entityA, entityB);
	}

	void Bounce(Entity entityA, Entity entityB)
	{
		auto& velA = Game::coordinator.GetComponent<VelocityComponent>(entityA);
		auto& posA = Game::coordinator.GetComponent<PositionComponent>(entityA);
		auto& colA = Game::coordinator.GetComponent<CollisionComponent>(entityA);

		auto& posB = Game::coordinator.GetComponent<PositionComponent>(entityB);
		auto& colB = Game::coordinator.GetComponent<CollisionComponent>(entityB);

		// Calculate overlap on each side of the collision
		float overlapLeft = (posA.x + colA.collider.w) - posB.x;
		float overlapRight = (posB.x + colB.collider.w) - posA.x;
		float overlapTop = (posA.y + colA.collider.h) - posB.y;
		float overlapBottom = (posB.y + colB.collider.h) - posA.y;

		// Determine which side the collision is coming from
		bool fromLeft = fabs(overlapLeft) < fabs(overlapRight);
		bool fromTop = fabs(overlapTop) < fabs(overlapBottom);

		// Find the minimum overlap in the X and Y axes
		float minOverlapX = fromLeft ? overlapLeft : overlapRight;
		float minOverlapY = fromTop ? overlapTop : overlapBottom;

		// Determine whether the collision is horizontal or vertical
		if (fabs(minOverlapX) < fabs(minOverlapY) || fabs(minOverlapX) == fabs(minOverlapY))
		{
			// Horizontal collision
			velA.x = -velA.x;
			colA.collisionSide = fromLeft ? Side::LEFT : Side::RIGHT;
		}
		else
		{
			// Vertical collision
			velA.y = -velA.y;
			colA.collisionSide = fromTop ? Side::TOP : Side::BOTTOM;
		}
	}

	SpatialHash spatialHash;
};
