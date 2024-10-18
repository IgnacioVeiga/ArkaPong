#pragma once

#include <SDL2/SDL.h>
#include "Scene.h"
#include "../Game.h"
#include "../ECS/Coordinator.h"
#include "../ECS/System/SpriteSystem.h"
#include "../ECS/System/InputSystem.h"
#include "../ECS/System/AudioSystem.h"
#include "../ECS/System/TextSystem.h"
#include "../ECS/System/Background/SolidColorBackgroundSystem.h"

class MainMenuScene : public Scene
{
public:
    void Init() override
    {
        sceneEntities["BlackBackground"] = CreateSolidColorBackgroundEntity(C_BLACK);

        // TODO: use a sprite as title
        sceneEntities["Title"] = CreateTextEntity(
            GAME_TITLE,
            C_WHITE,
            RETRO_FONT_FILEPATH,
            24,
            SCREEN_WIDTH / 2,
            PADDLE_OFFSET,
            TextAlignment::CENTER);

        // TODO: add menu options
        sceneEntities["Menu"] = CreateTextEntity(
            "Press ENTER",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            16,
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT / 2,
            TextAlignment::CENTER);

        sceneEntities["Footer"] = CreateTextEntity(
            "pre-alpha 2024",
            C_GRAY,
            RETRO_FONT_FILEPATH,
            8,
            SCREEN_WIDTH / 2,
            SCREEN_HEIGHT - PADDLE_OFFSET,
            TextAlignment::CENTER);
    };

    void Update(float deltaTime) override
    {
        Game::coordinator.GetSystem<SolidColorBackgroundSystem>()->Update();
        Game::coordinator.GetSystem<TextSystem>()->Update();

        // TODO: use the input system
        const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
        if (keyStates[SDL_SCANCODE_RETURN])
        {
            Game::sceneManager->ChangeScene("Game");
        }
    };

    void Cleanup() override
    {
        // Clean up entities and other resources
        for (const auto &entityPair : sceneEntities)
        {
            Game::coordinator.DestroyEntity(entityPair.second);
        }
        sceneEntities.clear();
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
