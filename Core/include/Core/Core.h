#pragma once

#include "Coordinator.h"
#include "Manager/SceneManager.h"
#include "Window.h"

namespace Core {
    inline Coordinator& GetCoordinator() {
        static Coordinator instance;
        return instance;
    }

    inline SceneManager& GetSceneManager() {
        static SceneManager instance;
        return instance;
    }

    inline Window& GetWindow() {
        static Window instance;
        return instance;
    }

    static bool is_game_on = true;
}
