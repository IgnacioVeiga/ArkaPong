#pragma once

#include "Entity.h"
#include "Core/Manager/FontManager.h"
#include "Core/Utils/Vec2.h"
#include "Core/Utils/CoreEnums.h"
#include "Core/Component/TextComponent.h"
#include "Core/Core.h"

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
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);

    Core::GetCoordinator().AddComponent(
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
