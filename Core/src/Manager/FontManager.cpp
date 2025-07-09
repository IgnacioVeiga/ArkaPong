#include "Core/Manager/FontManager.h"
#include <iostream>

TTF_Font* FontManager::GetFont(const std::string& path, const int size)
{
    const std::string key = path + std::to_string(size);
    if (fonts.find(key) == fonts.end())
    {
        TTF_Font* font = TTF_OpenFont(path.c_str(), size);
        if (!font)
        {
            std::cerr << "Error loading font'" << path << "': " << TTF_GetError() << std::endl;
            return nullptr;
        }
        fonts[key] = font;
    }
    return fonts[key];
}

void FontManager::Cleanup()
{
    for (const auto& [key, value] : fonts)
    {
        TTF_CloseFont(value);
    }
    fonts.clear();
}

std::unordered_map<std::string, TTF_Font*> FontManager::fonts;
