#pragma once
#include "Core/Entity/BackgroundEntity.h"
#include "Core/Entity/TextEntity.h"
#include "Core/Utils/Vec2.h"
#include "Core/Utils/CoreEnums.h"
#include "../Utils/GameConstants.h"
#include "Core/System/BaseSystem.h"

class MainMenuScene final : public Scene {
public:
    void Init() override {
        CreateSolidColorBackgroundEntity("BlackBG", TITLE_SCENE, C_BLACK);

        // TODO: use a sprite as title
        CreateTextEntity(
            "Title",
            TITLE_SCENE,
            DEFAULT_GAME_TITLE,
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_L,
            Vec2(static_cast<float_t>(SCREEN_WIDTH) / 2, PADDLE_OFFSET),
            Side::CENTER);

        // TODO: add menu options
        CreateTextEntity(
            "Menu",
            TITLE_SCENE,
            "Press ENTER",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(static_cast<float_t>(SCREEN_WIDTH) / 2, static_cast<float_t>(SCREEN_HEIGHT) / 2),
            Side::CENTER);

        CreateTextEntity(
            "Footer",
            TITLE_SCENE,
            "pre-alpha 2024",
            C_GRAY,
            RETRO_FONT_FILEPATH,
            FONT_XS,
            Vec2(static_cast<float_t>(SCREEN_WIDTH) / 2, SCREEN_HEIGHT - PADDLE_OFFSET),
            Side::CENTER);
    };

    void Update(float delta_time) override {
        Core::GetCoordinator().GetSystem<AudioSystem>()->Update();
        Core::GetCoordinator().GetSystem<InputSystem>()->Update();
        Core::GetCoordinator().GetSystem<SolidColorBackgroundSystem>()->Update();
        Core::GetCoordinator().GetSystem<SpriteSystem>()->Update();
        Core::GetCoordinator().GetSystem<TextSystem>()->Update();

        // TODO: use the input system
        if (const Uint8 *keyStates = SDL_GetKeyboardState(nullptr); keyStates[SDL_SCANCODE_RETURN]) {
            Core::GetSceneManager().ChangeScene(ROUND_SCENE);
        }
    };

    void Cleanup() override {
        Core::GetCoordinator().GetSystem<BaseSystem>()->DestroyEntitiesByScene(TITLE_SCENE);
    }
};
