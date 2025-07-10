#pragma once

#include <string>
#include <unordered_map>

#if defined(_MSC_VER)
#include <SDL_ttf.h>
#else
#include <SDL2/SDL_ttf.h>
#endif

class FontManager
{
public:
    static TTF_Font* GetFont(const std::string& path, int size);
    static void Cleanup();
private:
    static std::unordered_map<std::string, TTF_Font*> fonts;
};
