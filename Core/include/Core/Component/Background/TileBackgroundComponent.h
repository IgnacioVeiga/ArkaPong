#pragma once

#include <SDL2/SDL_render.h>
#include <string>

struct TileBackgroundComponent {
    SDL_Texture *tileTexture;

    int tileTextureWidth;
    int tileTextureHeight;

    int tileWidth;
    int tileHeight;

    int mapWidth;
    int mapHeight;

    std::vector<int> tiles;
    std::string texturePath;
};
