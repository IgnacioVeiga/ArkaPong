#pragma once
#include "Core/Utils/CoreConstants.h"

/*
	Example:
	SDL_Texture* imageTexture = LoadTexture("path/to/image_texture.png");
	Entity imageBackground = CreateImageBackgroundEntity(imageTexture, 800, 600);
*/
class ImageBackgroundSystem : public System {
public:
    void Init() {
        Signature signature;
        signature.set(Core::GetCoordinator().GetComponentType<ImageBackgroundComponent>());
        Core::GetCoordinator().SetSystemSignature<ImageBackgroundSystem>(signature);
    }

    void Update() {
        for (auto const &entity: mEntities) {
            auto &bg = Core::GetCoordinator().GetComponent<ImageBackgroundComponent>(entity);
            SDL_Rect dstRect = {(SCREEN_WIDTH - bg.width) / 2, (SCREEN_HEIGHT - bg.height) / 2, bg.width, bg.height};
            SDL_RenderCopy(Core::GetWindow().GetRenderer(), bg.imageTexture, nullptr, &dstRect);
        }
    }
};
