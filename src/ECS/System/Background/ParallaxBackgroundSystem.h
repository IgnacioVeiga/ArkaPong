#pragma once

#include "../../../Game.h"
#include "../../Coordinator.h"
#include "../../../Utils/Constants.h"
#include "../../Component/Background/ParallaxBackgroundComponent.h"

/*
    Example of how to use:
    std::vector<ParallaxLayer> parallaxLayers = {
        { LoadTexture("path/to/layer1.png"), 0.1f },
        { LoadTexture("path/to/layer2.png"), 0.2f },
        { LoadTexture("path/to/layer3.png"), 0.3f }
    };
    Entity parallaxBackground = CreateParallaxBackgroundEntity(parallaxLayers);
*/
class ParallaxBackgroundSystem : public System {
public:
    void Init()
    {
        Signature signature;
        signature.set(Game::coordinator.GetComponentType<ParallaxBackgroundComponent>());
        Game::coordinator.SetSystemSignature<ParallaxBackgroundSystem>(signature);
    }

    void Update(float cameraX, float cameraY) {
        for (auto const& entity : mEntities) {
            auto& bg = Game::coordinator.GetComponent<ParallaxBackgroundComponent>(entity);
            for (auto& layer : bg.layers) {
                SDL_Rect dstRect = { static_cast<int>(-cameraX * layer.scrollSpeed), static_cast<int>(-cameraY * layer.scrollSpeed), SCREEN_WIDTH, SCREEN_HEIGHT };
                SDL_RenderCopy(Game::window.GetRenderer(), layer.layerTexture, nullptr, &dstRect);
            }
        }
    }
};
