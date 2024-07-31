#pragma once

#include <iostream>
#include "../ECS/Entity/Entity.h"

void TriggerAction(Entity entity) {
    std::cout << "Event triggered for entity: " << entity << std::endl;
}
