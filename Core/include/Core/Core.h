#pragma once

#include "Utils/Coordinator.h"
#include "Manager/SceneManager.h"
#include "Utils/Window.h"
#include "Utils/Configuration.h"
#include <string>
#include <functional>
#include <SDL2/SDL.h>

namespace Core
{
    void Init(const std::string& config_path, const char* title);
    void Run();
    void CleanUp();

    Coordinator& GetCoordinator();
    SceneManager& GetSceneManager();
    Window& GetWindow();
    extern bool is_game_on;
    extern json config;

    using EventCallback = std::function<void(const SDL_Event&)>;
    void SetEventCallback(const EventCallback& callback);

    using UpdateCallback = std::function<void(float)>;
    void SetUpdateCallback(const UpdateCallback& callback);
}
