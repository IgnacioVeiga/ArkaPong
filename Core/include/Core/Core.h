#pragma once

#include "Utils/Coordinator.h"
#include "Manager/SceneManager.h"
#include "Utils/Window.h"

namespace Core {
    Coordinator& GetCoordinator();
    SceneManager& GetSceneManager();
    Window& GetWindow();
    static bool is_game_on = true;
}
