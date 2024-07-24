#pragma once

#include <set>
#include "../Entity/Entity.h"

class System
{
public:
    // For now we use the global entities, it would be better to use only the loaded scene entities.
    std::set<Entity> mEntities;
};
