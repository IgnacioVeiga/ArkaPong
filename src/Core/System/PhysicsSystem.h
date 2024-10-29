#pragma once

#include "../Utils/CoreConstants.h"
#include "../Utils/SpatialHash.h"

// Should not be here
#include "../../ArkaPong/Utils/GameConstants.h"

class PhysicsSystem : public System
{
public:
    void Init()
    {
        Signature signature{};
        signature.set(Game::coordinator.GetComponentType<RigidBodyComponent>());
        signature.set(Game::coordinator.GetComponentType<TransformComponent>());
        Game::coordinator.SetSystemSignature<PhysicsSystem>(signature);
    }

    void Update(float deltaTime)
    {
        spatialHash.Clear();
        PopulateSpatialHash();

        // Update movement of non-static entities
        for (auto const &entity : mEntities)
        {
            auto &rigidBody = Game::coordinator.GetComponent<RigidBodyComponent>(entity);
            if (!rigidBody.isStatic) ApplyPhysics(entity, deltaTime);

			CheckOutOfBounds(entity);
        }

        // List possible collisions and resolve
        std::vector<std::pair<Entity, Entity>> collisions;
        DetectCollisions(collisions);
        for (const auto &pair : collisions)
        {
            ResolveCollision(pair.first, pair.second);
        }
    }

private:
    void ApplyPhysics(Entity entity, float deltaTime)
    {
        auto &rigidBody = Game::coordinator.GetComponent<RigidBodyComponent>(entity);
        auto &transform = Game::coordinator.GetComponent<TransformComponent>(entity);

        // Gravity
        if (rigidBody.useGravity)
        {
            rigidBody.acceleration.y += GRAVITY * deltaTime;
        }

        // Update velocity and position using acceleration
        rigidBody.velocity += rigidBody.acceleration * deltaTime;
        transform.position += rigidBody.velocity * deltaTime;

        // Reset acceleration for the next cycle
        rigidBody.acceleration = Vec2(0.0f, 0.0f);
    }

    void PopulateSpatialHash()
    {
        for (const auto &entity : mEntities)
        {
            auto &rigidBody = Game::coordinator.GetComponent<RigidBodyComponent>(entity);
            auto &transform = Game::coordinator.GetComponent<TransformComponent>(entity);
            
            UpdateColliderPosition(rigidBody, transform);
            spatialHash.Insert(entity, rigidBody.collider);
        }
    }

    void UpdateColliderPosition(RigidBodyComponent &rigidBody, TransformComponent &transform)
    {
        rigidBody.collider.x = static_cast<int>(transform.position.x);
        rigidBody.collider.y = static_cast<int>(transform.position.y);
    }

    void DetectCollisions(std::vector<std::pair<Entity, Entity>> &collisions)
    {
        for (const auto &entity : mEntities)
        {
            auto &rigidBody = Game::coordinator.GetComponent<RigidBodyComponent>(entity);
            std::vector<Entity> possibleCollisions = spatialHash.Retrieve(rigidBody.collider);

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
        auto &colliderA = Game::coordinator.GetComponent<RigidBodyComponent>(entityA).collider;
        auto &colliderB = Game::coordinator.GetComponent<RigidBodyComponent>(entityB).collider;

        return SDL_HasIntersection(&colliderA, &colliderB);
    }

    void ResolveCollision(Entity entityA, Entity entityB)
    {
        auto &rigidBodyA = Game::coordinator.GetComponent<RigidBodyComponent>(entityA);
        auto &rigidBodyB = Game::coordinator.GetComponent<RigidBodyComponent>(entityB);

        // // Resolving the collision for non-static bodies
        // // TODO: Should use the same logic of "onCollision" callback of the ball entity?
        // if (!rigidBodyA.isStatic)
        // {
        //     // Reverse speed or apply another type of collision response.
        //     rigidBodyA.velocity = -rigidBodyA.velocity;
        // }
        // if (!rigidBodyB.isStatic)
        // {
        //     rigidBodyB.velocity = -rigidBodyB.velocity;
        // }

        // Calling collision callbacks if they exist
        if (rigidBodyA.onCollision)
            rigidBodyA.onCollision(entityA, entityB);
        if (rigidBodyB.onCollision)
            rigidBodyB.onCollision(entityB, entityA);
    }

    	void CheckOutOfBounds(Entity entity)
	{
		auto &transformComponent = Game::coordinator.GetComponent<TransformComponent>(entity);
		auto &rigidBodyComponent = Game::coordinator.GetComponent<RigidBodyComponent>(entity);

		// TODO: Define what should happen via a callback, for now this has the behavior of the ball.
		if (transformComponent.position.x > SCREEN_WIDTH || transformComponent.position.x < 0)
		{
			ResetEntityPositionAndVelocity(transformComponent, rigidBodyComponent);
		}

		if ((transformComponent.position.y + rigidBodyComponent.collider.h) > SCREEN_HEIGHT || transformComponent.position.y < 0)
		{
			rigidBodyComponent.velocity.y = -rigidBodyComponent.velocity.y;
		}
	}

    // TODO: move to ball entity as callback maybe
	void ResetEntityPositionAndVelocity(TransformComponent &transformComponent, RigidBodyComponent &rigidBodyComponent)
	{
		transformComponent.position = Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		rigidBodyComponent.velocity.x = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
		int factor = rand() % BALL_SPEED + 1;
		rigidBodyComponent.velocity.y = (rand() % 2 == 0 ? -factor : factor);
	}

    SpatialHash spatialHash;
};
