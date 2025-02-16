#pragma once

#include <string>
#include "../Core.h"
#include "../Component/AudioComponent.h"

void CreateSFXEntity(std::string entity_name, std::string scene_name, const std::string &path, bool loop = false, int channel = -1)
{
    Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);
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

void CreateBGMEntity(std::string entity_name, std::string scene_name, const std::string &path, bool loop = false)
{
    Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);
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
