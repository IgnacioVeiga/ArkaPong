#pragma once

#include <string>
#include <iostream>
#include <unordered_map>
#include <SDL_ttf.h>

class FontManager
{
public:
    static TTF_Font *GetFont(const std::string &path, int size)
    {
        std::string key = path + std::to_string(size);
        if (fonts.find(key) == fonts.end())
        {
            TTF_Font *font = TTF_OpenFont(path.c_str(), size);
            if (!font)
            {
                std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
                return nullptr;
            }
            fonts[key] = font;
        }
        return fonts[key];
    }

    static void Cleanup()
    {
        for (auto &pair : fonts)
        {
            TTF_CloseFont(pair.second);
        }
        fonts.clear();
    }

private:
    static std::unordered_map<std::string, TTF_Font *> fonts;
};

std::unordered_map<std::string, TTF_Font *> FontManager::fonts;
