#pragma once

#include <vector>
#include "../../Utils/CollisionReaction.h"

struct CollisionComponent
{
    SDL_Rect collider;
    std::vector<CollisionReaction> reactions;
};
