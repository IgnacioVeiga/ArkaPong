#pragma once

#include <functional>
#include <vector>
#include "../ECS/Entity/Entity.h"

struct CollisionReaction
{
    std::function<void(Entity, Entity)> reaction;

    CollisionReaction(std::function<void(Entity, Entity)> func) : reaction(func) {}
};

void PlaySound(Entity entityA, Entity entityB)
{
    AudioComponent audioComp = Game::coordinator.GetComponent<AudioComponent>(entityA);
    audioComp.isPlaying = true;
    audioComp = Game::coordinator.GetComponent<AudioComponent>(entityB);
    audioComp.isPlaying = true;
}

void DestroyEntity(Entity entityA, Entity entityB)
{
    // TODO: destroy entityA or entityB
}

void Bounce(Entity entityA, Entity entityB)
{
    // TODO: check whether both entities should bounce or just one of them
    VelocityComponent velComp = Game::coordinator.GetComponent<VelocityComponent>(entityA);
    // TODO: invert velComp.X or velComp.Y depending on the side of the collision.
}