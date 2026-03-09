#pragma once

#include <SDL2/SDL_render.h>
#include <string>
#include <unordered_map>
#include "Core/CoreExport.h"

class CORE_API TextureManager {
public:
    static SDL_Texture *LoadTexture(const std::string &path);
    static void Clear();
private:
    static std::unordered_map<std::string, SDL_Texture *> textureMap;
};
