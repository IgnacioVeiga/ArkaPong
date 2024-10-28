#pragma once

struct TileBackgroundComponent {
    SDL_Texture* tileTexture;

    int tileTextureWidth;
    int tileTextureHeight;

    int tileWidth;
    int tileHeight;

    int mapWidth;
    int mapHeight;

    std::vector<int> tiles;
};