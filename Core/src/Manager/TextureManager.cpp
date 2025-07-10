#include <iostream>

#include "Core/Core.h"
#include "Core/Manager/TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const std::string& path)
{
    // Check if texture is already loaded
    if (textureMap.find(path) != textureMap.end())
    {
        return textureMap[path];
    }

    // Load new texture if not found
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    if (!surface)
    {
        std::cerr << "Error loading BMP '" << path << "': " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Core::GetWindow().GetRenderer(), surface);
    SDL_FreeSurface(surface);

    if (!texture)
    {
        std::cerr << "Error creating texture '" << path << "': " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Store the texture in the map
    textureMap[path] = texture;

    return texture;
}

void TextureManager::Clear()
{
    // Free all textures
    for (const auto& [key, value] : textureMap)
    {
        SDL_DestroyTexture(value);
    }
    textureMap.clear();
}

std::unordered_map<std::string, SDL_Texture*> TextureManager::textureMap;
