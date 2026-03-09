#pragma once

#include "../Utils/GameEnums.h"

struct BrickComponent {
    BrickType type = BrickType::None;
    bool clearsLevel = true;
};

inline bool DoesBrickCountForLevelClear(const BrickType type)
{
    // Keeping gameplay-only ECS data in the example project shows how a game
    // can extend Core with custom components without editing the engine.
    return type != BrickType::None;
}
