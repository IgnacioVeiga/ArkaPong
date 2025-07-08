#pragma once

#include "Core/Component/Background/ParallaxLayer.h"
#include "Core/Manager/TextureManager.h"

inline void CreateTileBackgroundEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const std::string &texture_filepath
) {
    // Load the tile texture
    SDL_Texture *tileTexture = TextureManager::LoadTexture(texture_filepath);

    // Tile texture dimensions
    constexpr int tileTextureWidth = 160;
    constexpr int tileTextureHeight = 32;

    // Dimensions of each tile
    constexpr int tileWidth = 32;
    constexpr int tileHeight = 32;

    // Dimensions of the tile map (how many tiles in width and height)
    constexpr int mapWidth = SCREEN_WIDTH / tileWidth;
    constexpr int mapHeight = SCREEN_HEIGHT / tileHeight;

    const std::vector tiles(mapWidth * mapHeight, 0);

    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(entity, TileBackgroundComponent{
                                       tileTexture, tileTextureWidth, tileTextureHeight, tileWidth, tileHeight,
                                       mapWidth, mapHeight, tiles
                                   });
}

inline void CreateSolidColorBackgroundEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const SDL_Color color
) {
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(entity, SolidColorBackgroundComponent{color});
}

inline void CreateImageBackgroundEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    SDL_Texture *imageTexture,
    const int width,
    const int height
) {
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(entity, ImageBackgroundComponent{imageTexture, width, height});
}

inline void CreateParallaxBackgroundEntity(
    const std::string &entity_name,
    const std::string &scene_name,
    const std::vector<ParallaxLayer> &layers
) {
    const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
    Core::GetCoordinator().AddComponent(entity, ParallaxBackgroundComponent{layers});
}
// inline void CreateParallaxBackgroundEntity(
//     const std::string& entity_name,
//     const std::string& scene_name,
//     std::vector<ParallaxLayer>&& layers
// ) {
//     const Entity entity = Core::GetCoordinator().CreateEntity(entity_name, scene_name);
//     Core::GetCoordinator().AddComponent(entity, ParallaxBackgroundComponent{std::move(layers)});
// }
