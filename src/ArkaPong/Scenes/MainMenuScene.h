#pragma once
#include "../../Core/Entity/BackgroundEntity.h"
#include "../../Core/Entity/TextEntity.h"
#include "../../Core/Utils/Vec2.h"
#include "../../Core/Utils/CoreEnums.h"
#include "../Utils/GameConstants.h"

class MainMenuScene : public Scene
{
public:
    void Init() override
    {
        CreateSolidColorBackgroundEntity("BlackBG", TITLE_SCENE, C_BLACK);

        // TODO: use a sprite as title
        CreateTextEntity(
            "Title",
            TITLE_SCENE,
            DEFAULT_GAME_TITLE,
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_L,
            Vec2(SCREEN_WIDTH / 2, PADDLE_OFFSET),
            Side::CENTER);

        // TODO: add menu options
        CreateTextEntity(
            "Menu",
            TITLE_SCENE,
            "Press ENTER",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),
            Side::CENTER);

        CreateTextEntity(
            "Footer",
            TITLE_SCENE,
            "pre-alpha 2024",
            C_GRAY,
            RETRO_FONT_FILEPATH,
            FONT_XS,
            Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PADDLE_OFFSET),
            Side::CENTER);
    };

    void Update(float delta_time) override
    {
		Core::coordinator.GetSystem<AudioSystem>()->Update();
		Core::coordinator.GetSystem<InputSystem>()->Update();
		Core::coordinator.GetSystem<SolidColorBackgroundSystem>()->Update();
		Core::coordinator.GetSystem<SpriteSystem>()->Update();
		Core::coordinator.GetSystem<TextSystem>()->Update();

        // TODO: use the input system
        const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
        if (keyStates[SDL_SCANCODE_RETURN])
        {
            Core::scene_manager.ChangeScene(ROUND_SCENE);
        }
    };

    void Cleanup() override
    {
        Core::coordinator.GetSystem<BaseSystem>()->DestroyEntitiesByScene(TITLE_SCENE);
    }
};
