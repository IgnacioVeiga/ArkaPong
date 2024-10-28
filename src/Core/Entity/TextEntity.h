#pragma once

#include "../Manager/FontManager.h"
#include "../Utils/Vec2.h"
#include "../Utils/CoreEnums.h"

void CreateTextEntity(std::string entity_name, std::string scene_name, const std::string &text, const SDL_Color &color, const std::string &fontPath, int fontSize, Vec2 pos, Side alignment = Side::LEFT)
{
    TTF_Font *font = FontManager::GetFont(fontPath, fontSize);
    Entity entity = Game::coordinator.CreateEntity(entity_name, scene_name);

    Game::coordinator.AddComponent(
        entity,
        TextComponent{
            text,
            color,
            font,
            pos,
            nullptr, // Initially, there is no texture
            true,    // Needs to be updated
            alignment});
}
