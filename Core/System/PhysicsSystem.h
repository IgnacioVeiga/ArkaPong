#pragma once

#include <memory>
#include "../Entity/Entity.h"
#include "../Utils/CoreConstants.h"
#include "../Utils/CollisionDetection.h"
#include "../Utils/QuadTree.h"
#include "../Utils/SpatialHash.h"
#include "../ThirdParty/nlohmann-json/json.hpp"

class PhysicsSystem : public System {
public:
    void Init(const nlohmann::json &config) {
        Signature signature{};
        signature.set(Core::coordinator.GetComponentType<RigidBodyComponent>());
        signature.set(Core::coordinator.GetComponentType<TransformComponent>());
        Core::coordinator.SetSystemSignature<PhysicsSystem>(signature);

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
            auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);
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
            const auto &transform = Core::coordinator.GetComponent<TransformComponent>(entity);
            auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);

            // Update collider position
            rigidBody.collider.x = transform.position.x;
            rigidBody.collider.y = transform.position.y;

            collisionDetection->Insert(entity, transform.position, rigidBody.collider);
        }
    }

    void DetectCollisions(std::vector<std::pair<Entity, Entity> > &collisions) {
        for (const auto &entity: mEntities) {
            auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);
            std::vector<Entity> possibleCollisions = collisionDetection->Retrieve(rigidBody.collider);

            for (const auto &otherEntity: possibleCollisions) {
                if (entity == otherEntity || entity >= otherEntity)
                    continue;

                // Check collision
                auto &other_rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(otherEntity);
                if (SDL_HasIntersectionF(&rigidBody.collider, &other_rigidBody.collider)) {
                    collisions.emplace_back(entity, otherEntity);
                }
            }
        }
    }

    void ApplyPhysics(Entity entity, float delta_time) {
        auto &rigidBody = Core::coordinator.GetComponent<RigidBodyComponent>(entity);
        auto &transform = Core::coordinator.GetComponent<TransformComponent>(entity);

        if (rigidBody.useGravity) {
            rigidBody.acceleration.y += gravity * delta_time;
        }

        rigidBody.velocity += rigidBody.acceleration * delta_time;
        transform.position += rigidBody.velocity * delta_time;
        rigidBody.acceleration = Vec2(0.0f, 0.0f);
    }

    void ResolveCollision(Entity entityA, Entity entityB) {
        const auto &rigidbody_A = Core::coordinator.GetComponent<RigidBodyComponent>(entityA);
        const auto &rigidbody_B = Core::coordinator.GetComponent<RigidBodyComponent>(entityB);

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

    void Bounce(Entity self, Entity other) {
        auto &transform_self = Core::coordinator.GetComponent<TransformComponent>(self);
        auto &rigidbody_self = Core::coordinator.GetComponent<RigidBodyComponent>(self);

        const auto &transform_other = Core::coordinator.GetComponent<TransformComponent>(other);
        const auto &rigidbody_other = Core::coordinator.GetComponent<RigidBodyComponent>(other);

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
    void CheckOutOfBounds(Entity entity) {
        auto &transformComponent = Core::coordinator.GetComponent<TransformComponent>(entity);
        auto &rigidBodyComponent = Core::coordinator.GetComponent<RigidBodyComponent>(entity);

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
