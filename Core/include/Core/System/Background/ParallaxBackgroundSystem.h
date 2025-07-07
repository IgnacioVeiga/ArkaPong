#pragma once

/*
    Example:
    std::vector<ParallaxLayer> parallaxLayers = {
        { LoadTexture("path/to/layer1.png"), 0.1f },
        { LoadTexture("path/to/layer2.png"), 0.2f },
        { LoadTexture("path/to/layer3.png"), 0.3f }
    };
    Entity parallaxBackground = CreateParallaxBackgroundEntity(parallaxLayers);
*/
class ParallaxBackgroundSystem : public System {
public:
    void Init() {
        Signature signature;
        signature.set(Core::coordinator.GetComponentType<ParallaxBackgroundComponent>());
        Core::coordinator.SetSystemSignature<ParallaxBackgroundSystem>(signature);
    }

    void Update(const float cameraX, const float cameraY) {
        for (auto const &entity: mEntities) {
            auto &bg = Core::coordinator.GetComponent<ParallaxBackgroundComponent>(entity);
            for (const auto &layer: bg.layers) {
                SDL_Rect dstRect = {
                    static_cast<int>(-cameraX * layer.scrollSpeed), static_cast<int>(-cameraY * layer.scrollSpeed),
                    SCREEN_WIDTH, SCREEN_HEIGHT
                };
                SDL_RenderCopy(Core::window.GetRenderer(), layer.layerTexture, nullptr, &dstRect);
            }
        }
    }
};
