#pragma once

#include "Entity.h"
#include "../Coordinator.h"
#include "../../Utils/FontManager.h"
#include "../../Game.h"
#include "../Component/TextComponent.h"

Entity CreateTextEntity(const std::string &text, const SDL_Color &color, const std::string &fontPath, int fontSize, int x, int y, Side alignment = Side::LEFT)
{
    TTF_Font *font = FontManager::GetFont(fontPath, fontSize);
    Entity entity = Game::coordinator.CreateEntity();

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

    return entity;
}
