#pragma once

#include "../Utils/CoreConstants.h"

// May replace the collision system
class PhysicsSystem : public System
{
public:
    void Init()
    {
        Signature signature{};
        signature.set(Game::coordinator.GetComponentType<TransformComponent>());
        signature.set(Game::coordinator.GetComponentType<RigidBodyComponent>());
        Game::coordinator.SetSystemSignature<PhysicsSystem>(signature);
    }

    void Update(float deltaTime)
    {
        for (auto const &entity : mEntities)
        {
            auto &transformComponent = Game::coordinator.GetComponent<TransformComponent>(entity);
            auto &rigidBodyComponent = Game::coordinator.GetComponent<RigidBodyComponent>(entity);

            if (rigidBodyComponent.isStatic)
                continue;

            if (rigidBodyComponent.useGravity)
            {
                rigidBodyComponent.acceleration.y += GRAVITY * deltaTime;
            }

            rigidBodyComponent.velocity += rigidBodyComponent.acceleration * deltaTime;
            transformComponent.position += rigidBodyComponent.velocity * deltaTime;

            // Reset the acceleration after applying the calculations
            rigidBodyComponent.acceleration = Vec2(0.0f, 0.0f);
        }
    }

    void ApplyForce(RigidBodyComponent &rigidBody, Vec2 force)
    {
        rigidBody.acceleration += Vec2(force.x / rigidBody.mass, force.y / rigidBody.mass);
    }
};
