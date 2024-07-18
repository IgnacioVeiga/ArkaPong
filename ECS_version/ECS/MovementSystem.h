#pragma once

#include "System.h"
#include "PositionComponent.h"

class MovementSystem : public System
{
public:
    void Update(float deltaTime) override { }

	// System.h implementation, may be unnecessary
    void Render() override { }
};
