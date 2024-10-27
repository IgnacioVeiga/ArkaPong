#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Utils/FontManager.h"
#include "../../Game.h"
#include "../Component/TextComponent.h"

void CreateTextEntity(std::string entity_name, std::string scene_name, const std::string &text, const SDL_Color &color, const std::string &fontPath, int fontSize, int x, int y, Side alignment = Side::LEFT)
{
    TTF_Font *font = FontManager::GetFont(fontPath, fontSize);
    Entity entity = Game::coordinator.CreateEntity(entity_name, scene_name);

    Game::coordinator.AddComponent(
        entity,
        TextComponent{
            text,
            color,
            font,
            x,
            y,
            nullptr, // Initially, there is no texture
            true,    // Needs to be updated
            alignment});
}
