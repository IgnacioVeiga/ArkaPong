#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

struct TextComponent
{
    std::string text;
    SDL_Color color;
    TTF_Font *font;
    SDL_Rect destRect;
};
