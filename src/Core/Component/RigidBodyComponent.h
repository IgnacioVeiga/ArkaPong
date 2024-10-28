#pragma once

#include "../Utils/Vec2.h"

struct RigidBodyComponent
{
    Vec2 velocity = Vec2(0.0f, 0.0f);     // May replace the VelocityComponent
    Vec2 acceleration = Vec2(0.0f, 0.0f); // Can change depending on the force applied
    float mass = 1.0f;                    // For collisions and force
    bool isStatic = false;                // If true, the entity should not move such as walls, static platforms, etc.
    bool useGravity = true;
};
