#pragma once

class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const std::string &path)
    {
        // Check if texture is already loaded
        if (textureMap.find(path) != textureMap.end())
        {
            return textureMap[path];
        }

        // Load new texture if not found
        SDL_Surface *surface = SDL_LoadBMP(path.c_str());
        if (!surface)
        {
            std::cerr << "Error loading BMP: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(Core::window.GetRenderer(), surface);
        SDL_FreeSurface(surface);

        if (!texture)
        {
            std::cerr << "Error creating texture: " << SDL_GetError() << std::endl;
            return nullptr;
        }

        // Store the texture in the map
        textureMap[path] = texture;

        return texture;
    }

    static void Clear()
    {
        // Free all textures
        for (auto &pair : textureMap)
        {
            SDL_DestroyTexture(pair.second);
        }
        textureMap.clear();
    }

private:
    static std::unordered_map<std::string, SDL_Texture *> textureMap;
};

std::unordered_map<std::string, SDL_Texture *> TextureManager::textureMap;
