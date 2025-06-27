#pragma once

#include "Entity.h"
#include "../Manager/FontManager.h"
#include "../Utils/Vec2.h"
#include "../Utils/CoreEnums.h"
#include "../Core.h"
#include "../Component/TextComponent.h"

inline void CreateTextEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const std::string &text,
    const SDL_Color &color,
    const std::string &fontPath,
    const int fontSize,
    const Vec2 pos,
    const Side alignment = Side::LEFT
) {
    TTF_Font *font = FontManager::GetFont(fontPath, fontSize);
    const Entity entity = Core::coordinator.CreateEntity(entity_name, scene_name);

    Core::coordinator.AddComponent(
        entity,
        TextComponent{
            text,
            color,
            font,
            pos,
            nullptr, // Initially, there is no texture
            true, // Needs to be updated
            alignment
        });
}
