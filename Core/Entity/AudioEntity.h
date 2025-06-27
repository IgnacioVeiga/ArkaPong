#pragma once

#include <string>
#include "../Core.h"
#include "../Component/AudioComponent.h"

inline void CreateSFXEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const std::string &path,
    const bool loop = false,
    const int channel = -1
) {
    const Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);
    Core::coordinator.AddComponent(
        entity,
        AudioComponent{
            path,
            AudioType::SFX,
            true, // isPlaying
            loop,
            channel // -1 for automatic channel assignment
        });
}

inline void CreateBGMEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const std::string &path,
    const bool loop = false
) {
    const Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);
    Core::coordinator.AddComponent(
        entity,
        AudioComponent{
            path,
            AudioType::BGM,
            true, // isPlaying
            loop,
            -1 // BGM does not use channels
        });
}
