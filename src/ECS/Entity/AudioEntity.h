#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Game.h"
#include "../../Utils/AudioManager.h"
#include "../Component/AudioComponent.h"

Entity CreateSFXEntity(const std::string &path, bool loop = false, int channel = -1)
{
    Entity entity = Game::coordinator.CreateEntity();
    Game::coordinator.AddComponent(
        entity,
        AudioComponent{
            path,
            AudioType::SFX,
            true, // isPlaying
            loop,
            channel // -1 for automatic channel assignment
        });
    return entity;
}

Entity CreateBGMEntity(const std::string &path, bool loop = false)
{
    Entity entity = Game::coordinator.CreateEntity();
    Game::coordinator.AddComponent(
        entity,
        AudioComponent{
            path,
            AudioType::BGM,
            true, // isPlaying
            loop,
            -1 // BGM does not use channels
        });
    return entity;
}
