#pragma once

#include <utility>
#include <vector>

#include "Core/Component/InputComponent.h"
#include "Core/Core.h"

inline void CreateInputEntity(
    const std::string& entity_name,
    const std::string& scene_name,
    std::vector<InputBehavior> keyMappings,
    const Uint32 debounce_time = 250,
    const std::string& tag = "Input",
    const std::string& sub_tag = "")
{
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name, tag, sub_tag);

    // Input-only entities keep menu actions and scene transitions inside ECS
    // without forcing those commands to live in ad-hoc SDL polling code.
    Core::GetCoordinator().AddComponent(
        entity,
        InputComponent{std::move(keyMappings), debounce_time});
}
