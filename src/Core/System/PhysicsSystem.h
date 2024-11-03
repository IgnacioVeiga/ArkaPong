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
        signature.set(Core::coordinator.GetComponentType<RigidBodyComponent>());
        signature.set(Core::coordinator.GetComponentType<TransformComponent>());
        Core::coordinator.SetSystemSignature<PhysicsSystem>(signature);
    }

    void Update(float delta_time)
    {
        spatialHash.Clear();
        PopulateSpatialHash();

        // Update movement of non-static entities
        for (auto const &entity : mEntities)
        {
            auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);
            if (!rigidBody.isStatic)
                ApplyPhysics(entity, delta_time);

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
    void ApplyPhysics(Entity entity, float delta_time)
    {
        auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);
        auto &transform = Core::coordinator.GetComponent<TransformComponent>(entity);

        // Gravity
        if (rigidBody.useGravity)
        {
            rigidBody.acceleration.y += GRAVITY * delta_time;
        }

        // Update velocity and position using acceleration
        rigidBody.velocity += rigidBody.acceleration * delta_time;
        transform.position += rigidBody.velocity * delta_time;

        // Reset acceleration for the next cycle
        rigidBody.acceleration = Vec2(0.0f, 0.0f);
    }

    void PopulateSpatialHash()
    {
        for (const auto &entity : mEntities)
        {
            auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);
            auto &transform = Core::coordinator.GetComponent<TransformComponent>(entity);

            UpdateColliderPosition(rigidBody, transform);
            spatialHash.Insert(entity, rigidBody.collider);
        }
    }

    void UpdateColliderPosition(RigidBodyComponent &rigidBody, TransformComponent &transform)
    {
        rigidBody.collider.x = transform.position.x;
        rigidBody.collider.y = transform.position.y;
    }

    void DetectCollisions(std::vector<std::pair<Entity, Entity>> &collisions)
    {
        for (const auto &entity : mEntities)
        {
            auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);
            std::vector<Entity> possibleCollisions = spatialHash.Retrieve(rigidBody.collider);

            for (const auto &otherEntity : possibleCollisions)
            {
                if (entity == otherEntity || entity >= otherEntity)
                    continue;

                // Check collision
                auto &other_rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(otherEntity);
                if (SDL_HasIntersectionF(&rigidBody.collider, &other_rigidBody.collider))
                {
                    collisions.emplace_back(entity, otherEntity);
                }
            }
        }
    }

    void ResolveCollision(Entity entityA, Entity entityB)
    {
        auto &rigidbody_A = Core::coordinator.GetComponent<RigidBodyComponent>(entityA);
        auto &rigidbody_B = Core::coordinator.GetComponent<RigidBodyComponent>(entityB);

        // Resolving the collision for non-static bodies
        if (!rigidbody_A.isStatic)
            Bounce(entityA, entityB);
        if (!rigidbody_B.isStatic)
            Bounce(entityB, entityA);

        // Calling collision callbacks if they exist
        if (rigidbody_A.onCollision)
            rigidbody_A.onCollision(entityA, entityB);
        if (rigidbody_B.onCollision)
            rigidbody_B.onCollision(entityB, entityA);
    }

    void Bounce(Entity self, Entity other)
    {
        auto &transform_self = Core::coordinator.GetComponent<TransformComponent>(self);
        auto &rigidbody_self = Core::coordinator.GetComponent<RigidBodyComponent>(self);

        auto &transform_other = Core::coordinator.GetComponent<TransformComponent>(other);
        auto &rigidbody_other = Core::coordinator.GetComponent<RigidBodyComponent>(other);

        // Calculate overlap on each side of the collision
        float overlapLeft = (transform_self.position.x + rigidbody_self.collider.w) - transform_other.position.x;
        float overlapRight = (transform_other.position.x + rigidbody_other.collider.w) - transform_self.position.x;
        float overlapTop = (transform_self.position.y + rigidbody_self.collider.h) - transform_other.position.y;
        float overlapBottom = (transform_other.position.y + rigidbody_other.collider.h) - transform_self.position.y;

        // Determine which side the collision is coming from
        bool fromLeft = fabs(overlapLeft) < fabs(overlapRight);
        bool fromTop = fabs(overlapTop) < fabs(overlapBottom);

        // Find the minimum overlap in the X and Y axes
        float minOverlapX = fromLeft ? overlapLeft : overlapRight;
        float minOverlapY = fromTop ? overlapTop : overlapBottom;

        // Determine whether the collision is horizontal, vertical or diagonal
        if (fabs(minOverlapX) < fabs(minOverlapY))
        {
            // Horizontal collision
            rigidbody_self.velocity.x = -rigidbody_self.velocity.x;
            // Separate the ball by a small amount
            transform_self.position.x += fromLeft ? -minOverlapX : minOverlapX;
        }
        else if (fabs(minOverlapX) > fabs(minOverlapY))
        {
            // Vertical collision
            rigidbody_self.velocity.y = -rigidbody_self.velocity.y;
            // Separate the ball by a small amount
            transform_self.position.y += fromTop ? -minOverlapY : minOverlapY;
        }
        else
        {
            // Diagonal collision
            rigidbody_self.velocity.x = -rigidbody_self.velocity.x;
            rigidbody_self.velocity.y = -rigidbody_self.velocity.y;
            // Separate the ball by a small amount
            transform_self.position.y += fromTop ? -minOverlapY : minOverlapY;
            transform_self.position.x += fromLeft ? -minOverlapX : minOverlapX;
        }
    }

    // Destroy entity?
    void CheckOutOfBounds(Entity entity)
    {
        auto &transformComponent = Core::coordinator.GetComponent<TransformComponent>(entity);
        auto &rigidBodyComponent = Core::coordinator.GetComponent<RigidBodyComponent>(entity);

        // TODO: use a trigger rectangle
        if (transformComponent.position.x > SCREEN_WIDTH || transformComponent.position.x < 0)
        {
            ResetEntityPositionAndVelocity(transformComponent, rigidBodyComponent);
        }

        // TODO: use walls instead
        if ((transformComponent.position.y + rigidBodyComponent.collider.h) > SCREEN_HEIGHT || transformComponent.position.y < 0)
        {
            rigidBodyComponent.velocity.y = -rigidBodyComponent.velocity.y;
        }
    }

    // Duplicated code
    // TODO: remove later
    void ResetEntityPositionAndVelocity(TransformComponent &transformComponent, RigidBodyComponent &rigidBodyComponent)
    {
        transformComponent.position = Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        rigidBodyComponent.velocity.x = (rand() % 2 == 0 ? -BALL_SPEED : BALL_SPEED);
        float factor = static_cast<float>(rand() % static_cast<int>(BALL_SPEED) + 1);
        rigidBodyComponent.velocity.y = (rand() % 2 == 0 ? -factor : factor);
    }

    SpatialHash spatialHash;
};
