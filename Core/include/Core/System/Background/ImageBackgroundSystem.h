#pragma once

/*
	Example:
	SDL_Texture* imageTexture = LoadTexture("path/to/image_texture.png");
	Entity imageBackground = CreateImageBackgroundEntity(imageTexture, 800, 600);
*/
class ImageBackgroundSystem : public System {
public:
    void Init() {
        Signature signature;
        signature.set(Core::coordinator.GetComponentType<ImageBackgroundComponent>());
        Core::coordinator.SetSystemSignature<ImageBackgroundSystem>(signature);
    }

    void Update() {
        for (auto const &entity: mEntities) {
            auto &bg = Core::coordinator.GetComponent<ImageBackgroundComponent>(entity);
            SDL_Rect dstRect = {(SCREEN_WIDTH - bg.width) / 2, (SCREEN_HEIGHT - bg.height) / 2, bg.width, bg.height};
            SDL_RenderCopy(Core::window.GetRenderer(), bg.imageTexture, nullptr, &dstRect);
        }
    }
};
