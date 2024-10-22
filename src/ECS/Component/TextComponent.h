#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

struct TextComponent
{
    std::string text;
    SDL_Color color;
    TTF_Font *font;
    int x;
    int y;
    SDL_Texture *texture = nullptr; // New texture for storing rendered text
    bool dirty = true;              // Indicates if the text has changed and needs to be rendered again
    Side alignment = Side::LEFT;    // Text horizontal alignment
};
