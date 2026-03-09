#pragma once

#include "Utils/Coordinator.h"
#include "Manager/SceneManager.h"
#include "Utils/Window.h"
#include "Utils/Configuration.h"
#include "CoreExport.h"
#include <string>
#include <functional>
#include <vector>
#include <SDL2/SDL.h>

namespace Core
{
    CORE_API void Init(const std::string& config_path, const char* title);
    CORE_API void Run();
    CORE_API bool IsInitialized();

    CORE_API Coordinator& GetCoordinator();
    CORE_API SceneManager& GetSceneManager();
    CORE_API Window& GetWindow();
    CORE_API extern bool is_game_on;
    CORE_API extern json config;

    using InitCallback = std::function<void()>;
    CORE_API void SetInitCallback(const InitCallback& callback);
    CORE_API void AddInitCallback(const InitCallback& callback);
    CORE_API void ClearInitCallbacks();

    using EventCallback = std::function<void(const SDL_Event&)>;
    CORE_API void SetEventCallback(const EventCallback& callback);
    CORE_API void AddEventCallback(const EventCallback& callback);
    CORE_API void ClearEventCallbacks();

    using UpdateCallback = std::function<void(float)>;
    CORE_API void SetUpdateCallback(const UpdateCallback& callback);
    CORE_API void AddUpdateCallback(const UpdateCallback& callback);
    CORE_API void ClearUpdateCallbacks();
}
