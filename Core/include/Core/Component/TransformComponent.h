#pragma once

#include "Core/Utils/Vec2.h"

struct TransformComponent {
    Vec2 position;
    Vec2 scale = Vec2(1.0f, 1.0f);
    float rotation = 0.0f;
};
