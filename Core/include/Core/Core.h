#pragma once

#include "Utils/Coordinator.h"
#include "Manager/SceneManager.h"
#include "Utils/Window.h"
#include "Utils/Configuration.h"
#include <string>

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
}
