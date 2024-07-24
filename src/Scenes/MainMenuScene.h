#pragma once

#include <SDL2/SDL.h>
#include "Scene.h"
#include "../Game.h"
#include "../ECS/Coordinator.h"
#include "../ECS/System/RenderSystem.h"
#include "../ECS/System/InputSystem.h"
#include "../ECS/System/AudioSystem.h"
#include "../ECS/System/TextSystem.h"


class MainMenuScene : public Scene
{
public:
    void Init() override
    {
        // TODO: Add title, menu options and footer text
    };

    void Update(float deltaTime) override
    {
        Game::coordinator.GetSystem<RenderSystem>()->Update();
        Game::coordinator.GetSystem<InputSystem>()->Update();
        Game::coordinator.GetSystem<AudioSystem>()->Update();
        Game::coordinator.GetSystem<TextSystem>()->Update();
    };
};
