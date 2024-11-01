#pragma once

class TileBackgroundSystem : public System {
public:
    void Init()
    {
        Signature signature{};
        signature.set(Core::coordinator.GetComponentType<TileBackgroundComponent>());
        Core::coordinator.SetSystemSignature<TileBackgroundSystem>(signature);
    }

    void Update()
    {
        for (auto const& entity : mEntities)
        {
            auto& bg = Core::coordinator.GetComponent<TileBackgroundComponent>(entity);
            SDL_Rect srcRect{};
            SDL_Rect destRect{};

            int tilesPerRow = bg.tileTextureWidth / bg.tileWidth;
            for (int y = 0; y < bg.mapHeight; ++y)
            {
                for (int x = 0; x < bg.mapWidth; ++x)
                {
                    int tileIndex = bg.tiles[y * bg.mapWidth + x];
                    srcRect.x = (tileIndex % tilesPerRow) * bg.tileWidth;
                    srcRect.y = (tileIndex / tilesPerRow) * bg.tileHeight;
                    srcRect.w = bg.tileWidth;
                    srcRect.h = bg.tileHeight;

                    destRect.x = x * bg.tileWidth;
                    destRect.y = y * bg.tileHeight;
                    destRect.w = bg.tileWidth;
                    destRect.h = bg.tileHeight;

                    SDL_RenderCopy(Core::window.GetRenderer(), bg.tileTexture, &srcRect, &destRect);
                }
            }
        }
    }
};
