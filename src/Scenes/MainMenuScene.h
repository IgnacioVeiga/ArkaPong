#pragma once

#include <SDL2/SDL.h>
#include "Scene.h"
#include "../Game.h"
#include "../ECS/Coordinator.h"
#include "../ECS/System/BaseSystem.h"

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
            24,
            SCREEN_WIDTH / 2,
            PADDLE_OFFSET,
            Side::CENTER);

        // TODO: add menu options
        CreateTextEntity(
            "Menu",
            "MainMenu",
            "Press ENTER",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            16,
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT / 2,
            Side::CENTER);

        CreateTextEntity(
            "Footer",
            "MainMenu",
            "pre-alpha 2024",
            C_GRAY,
            RETRO_FONT_FILEPATH,
            8,
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT - PADDLE_OFFSET,
            Side::CENTER);
    };

    void Update(float deltaTime) override
    {
        Game::coordinator.GetSystem<BaseSystem>()->Update(deltaTime);

        // TODO: use the input system
        const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
        if (keyStates[SDL_SCANCODE_RETURN])
        {
            Game::sceneManager->ChangeScene("Game");
        }
    };

    void Cleanup() override
    {
        Game::coordinator.GetSystem<BaseSystem>()->DestroyEntitiesByScene("MainMenu");
    }

    void Pause() override
    {
        // Pause logic
    }

    void Resume() override
    {
        // Resume logic
    }

    bool SaveState(const std::string &filepath) override
    {
        // Serialize the scene state to a file
        return true;
    }

    bool LoadState(const std::string &filepath) override
    {
        // Deserialize the scene state from a file
        return true;
    }
};
