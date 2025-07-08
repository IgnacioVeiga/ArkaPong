#pragma once

#include <memory>
#include "Core/Entity/Entity.h"
#include "Core/Utils/CoreConstants.h"
#include "Core/Utils/CollisionDetection.h"
#include "Core/Utils/QuadTree.h"
#include "Core/Utils/SpatialHash.h"
#include "nlohmann-json/json.hpp"

class PhysicsSystem : public System {
public:
    void Init(const nlohmann::json &config) {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<RigidBodyComponent>());
        signature.set(Core::GetCoordinator().GetComponentType<TransformComponent>());
        Core::GetCoordinator().SetSystemSignature<PhysicsSystem>(signature);

        std::string collisionMethod = config["physics"]["collision_method"];
        if (collisionMethod == "quadtree") {
            collisionDetection = std::make_unique<QuadTree>();
        } else if (collisionMethod == "spatial_hash") {
            collisionDetection = std::make_unique<SpatialHash>();
        }

        gravity = config["physics"]["gravity"];
        std::cout << "Using " << collisionMethod << std::endl;
    }

    void Update(float delta_time) {
        collisionDetection->Clear();
        PopulateCollisionDetection();

        // Update movement of non-static entities
        for (auto const &entity: mEntities) {
            auto &rigidBody = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entity);
            if (!rigidBody.isStatic)
                ApplyPhysics(entity, delta_time);

            CheckOutOfBounds(entity);
        }

        // List possible collisions and resolve
        std::vector<std::pair<Entity, Entity> > collisions;
        DetectCollisions(collisions);
        // collisionDetection->GetPotentialCollisions(collisions);
        for (const auto &pair: collisions) {
            std::cout << "Collision detected between entities: " << pair.first << " and " << pair.second << std::endl;
            ResolveCollision(pair.first, pair.second);
        }
    }

private:
    void PopulateCollisionDetection() {
        for (auto const &entity: mEntities) {
            const auto &transform = Core::GetCoordinator().GetComponent<TransformComponent>(entity);
            auto &rigidBody = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entity);

            // Update collider position
            rigidBody.collider.x = transform.position.x;
            rigidBody.collider.y = transform.position.y;

            collisionDetection->Insert(entity, transform.position, rigidBody.collider);
        }
    }

    void DetectCollisions(std::vector<std::pair<Entity, Entity> > &collisions) {
        for (const auto &entity: mEntities) {
            auto &rigidBody = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entity);
            std::vector<Entity> possibleCollisions = collisionDetection->Retrieve(rigidBody.collider);

            for (const auto &otherEntity: possibleCollisions) {
                if (entity == otherEntity || entity >= otherEntity)
                    continue;

                // Check collision
                auto &other_rigidBody = Core::GetCoordinator().GetComponent<RigidBodyComponent>(otherEntity);
                if (SDL_HasIntersectionF(&rigidBody.collider, &other_rigidBody.collider)) {
                    collisions.emplace_back(entity, otherEntity);
                }
            }
        }
    }

    void ApplyPhysics(const Entity entity, const float delta_time) {
        auto &rigidBody = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entity);
        auto &transform = Core::GetCoordinator().GetComponent<TransformComponent>(entity);

        if (rigidBody.useGravity) {
            rigidBody.acceleration.y += gravity * delta_time;
        }

        rigidBody.velocity += rigidBody.acceleration * delta_time;
        transform.position += rigidBody.velocity * delta_time;
        rigidBody.acceleration = Vec2(0.0f, 0.0f);
    }

    void ResolveCollision(const Entity entityA, const Entity entityB) {
        const auto &rigidbody_A = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entityA);
        const auto &rigidbody_B = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entityB);

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

    void Bounce(const Entity self, const Entity other) {
        auto &transform_self = Core::GetCoordinator().GetComponent<TransformComponent>(self);
        auto &rigidbody_self = Core::GetCoordinator().GetComponent<RigidBodyComponent>(self);

        const auto &transform_other = Core::GetCoordinator().GetComponent<TransformComponent>(other);
        const auto &rigidbody_other = Core::GetCoordinator().GetComponent<RigidBodyComponent>(other);

        // Calculate overlap on each side of the collision
        const float overlapLeft = (transform_self.position.x + rigidbody_self.collider.w) - transform_other.position.x;
        const float overlapRight = (transform_other.position.x + rigidbody_other.collider.w) - transform_self.position.x;
        const float overlapTop = (transform_self.position.y + rigidbody_self.collider.h) - transform_other.position.y;
        const float overlapBottom = (transform_other.position.y + rigidbody_other.collider.h) - transform_self.position.y;

        // Side of collision coming from
        const bool fromLeft = fabs(overlapLeft) < fabs(overlapRight);
        const bool fromTop = fabs(overlapTop) < fabs(overlapBottom);

        // Find the minimum overlap in the X and Y axes
        const float minOverlapX = fromLeft ? overlapLeft : overlapRight;
        const float minOverlapY = fromTop ? overlapTop : overlapBottom;

        // Determine whether the collision is horizontal, vertical or diagonal
        if (fabs(minOverlapX) < fabs(minOverlapY)) {
            // Horizontal collision
            rigidbody_self.velocity.x = -rigidbody_self.velocity.x;
            // Separate the ball by a small amount
            transform_self.position.x += fromLeft ? -minOverlapX : minOverlapX;
        } else if (fabs(minOverlapX) > fabs(minOverlapY)) {
            // Vertical collision
            rigidbody_self.velocity.y = -rigidbody_self.velocity.y;
            // Separate the ball by a small amount
            transform_self.position.y += fromTop ? -minOverlapY : minOverlapY;
        } else {
            // Diagonal collision
            rigidbody_self.velocity.x = -rigidbody_self.velocity.x;
            rigidbody_self.velocity.y = -rigidbody_self.velocity.y;
            // Separate the ball by a small amount
            transform_self.position.y += fromTop ? -minOverlapY : minOverlapY;
            transform_self.position.x += fromLeft ? -minOverlapX : minOverlapX;
        }
    }

    // Depends, the entity can be destroyed, teleported, etc.
    // TODO: use callbacks or events for this
    void CheckOutOfBounds(const Entity entity) {
        auto &transformComponent = Core::GetCoordinator().GetComponent<TransformComponent>(entity);
        auto &rigidBodyComponent = Core::GetCoordinator().GetComponent<RigidBodyComponent>(entity);

        // Teleports to the center of the screen
        if (transformComponent.position.x > SCREEN_WIDTH || transformComponent.position.x < 0) {
            transformComponent.position = Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        }
        // Bounce vertically
        if ((transformComponent.position.y + rigidBodyComponent.collider.h) > SCREEN_HEIGHT || transformComponent.
            position.y < 0) {
            rigidBodyComponent.velocity.y = -rigidBodyComponent.velocity.y;
        }
    }

    std::unique_ptr<CollisionDetection> collisionDetection;
    float gravity = 0;
};
