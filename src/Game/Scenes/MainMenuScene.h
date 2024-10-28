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
        CreateSolidColorBackgroundEntity("BlackBG", "MainMenu", C_BLACK);

        // TODO: use a sprite as title
        CreateTextEntity(
            "Title",
            "MainMenu",
            GAME_TITLE,
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_L,
            Vec2(SCREEN_WIDTH / 2, PADDLE_OFFSET),
            Side::CENTER);

        // TODO: add menu options
        CreateTextEntity(
            "Menu",
            "MainMenu",
            "Press ENTER",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2),
            Side::CENTER);

        CreateTextEntity(
            "Footer",
            "MainMenu",
            "pre-alpha 2024",
            C_GRAY,
            RETRO_FONT_FILEPATH,
            FONT_XS,
            Vec2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - PADDLE_OFFSET),
            Side::CENTER);
    };

    void Update(float deltaTime) override
    {
        Game::coordinator.GetSystem<BaseSystem>()->Update(deltaTime);

        // TODO: use the input system
        const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
        if (keyStates[SDL_SCANCODE_RETURN])
        {
            Game::scene_manager.ChangeScene("Game");
        }
    };

    void Cleanup() override
    {
        Game::coordinator.GetSystem<BaseSystem>()->DestroyEntitiesByScene("MainMenu");
    }
};
