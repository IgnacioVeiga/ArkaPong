#pragma once

#include <string>
#include "Core/Core.h"
#include "Core/Component/AudioComponent.h"

inline void CreateSFXEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const std::string &path,
    const bool loop = false,
    const int channel = -1
) {
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(
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
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(
        entity,
        AudioComponent{
            path,
            AudioType::BGM,
            true, // isPlaying
            loop,
            -1 // BGM does not use channels
        });
}

inline void CreateAudioEntity(
    const std::string& entity_name,
    const std::string& scene_name,
    const std::string& path,
    const AudioType type,
    const bool loop = false,
    const int channel = -1
) {
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(
        entity,
        AudioComponent{
            path, type, true, loop, channel
        });
}

