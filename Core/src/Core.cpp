#include "Core/Core.h"
#include "Core/Utils/Configuration.h"
#include "Core/Utils/Window.h"
#include "Core/Manager/SceneManager.h"
#include "Core/System/BaseSystem.h"
#include "Core/Component/BaseComponent.h"
#include <cstdlib>
#include <ctime>
#include <vector>

namespace Core
{
    bool is_game_on = true;
    json config;

    namespace
    {
        bool core_initialized = false;
        std::vector<InitCallback> init_callbacks;
        std::vector<EventCallback> event_callbacks;
        std::vector<UpdateCallback> update_callbacks;
    }

    bool IsInitialized() {
        return core_initialized;
    }

    void SetInitCallback(const InitCallback& callback) {
        init_callbacks.clear();
        AddInitCallback(callback);
    }

    void AddInitCallback(const InitCallback& callback) {
        if (!callback) {
            return;
        }

        if (core_initialized) {
            // Late registrations are executed immediately so game projects can
            // extend the engine after Core::Init without editing the engine.
            callback();
            return;
        }

        init_callbacks.push_back(callback);
    }

    void ClearInitCallbacks() {
        init_callbacks.clear();
    }

    void SetEventCallback(const EventCallback& callback) {
        event_callbacks.clear();
        AddEventCallback(callback);
    }

    void AddEventCallback(const EventCallback& callback) {
        if (!callback) {
            return;
        }
        event_callbacks.push_back(callback);
    }

    void ClearEventCallbacks() {
        event_callbacks.clear();
    }

    void SetUpdateCallback(const UpdateCallback& callback) {
        update_callbacks.clear();
        AddUpdateCallback(callback);
    }

    void AddUpdateCallback(const UpdateCallback& callback) {
        if (!callback) {
            return;
        }
        update_callbacks.push_back(callback);
    }

    void ClearUpdateCallbacks() {
        update_callbacks.clear();
    }

    void Init(const std::string& config_path, const char* title)
    {
        srand(static_cast<Uint32>(time(nullptr)));

        config = readConfig(config_path);
        mergeConfig(config, getDefaultConfig());

        if (!GetWindow().Init(title, config))
        {
            is_game_on = false;
            return;
        }

        GetCoordinator().Init();
        GetCoordinator().RegisterComponent<BaseComponent>();
        GetCoordinator().RegisterSystem<BaseSystem>()->Init(config);

        core_initialized = true;

        // Iterate over a snapshot so callbacks can register extra hooks safely
        // during initialization without invalidating the active traversal.
        const auto initCallbacksSnapshot = init_callbacks;
        for (const auto& callback : initCallbacksSnapshot)
        {
            callback();
        }
    }

    void Run()
    {
        Uint32 last_frame_time = SDL_GetTicks();
        SDL_Event event;

        while (is_game_on)
        {
            const Uint32 current_frame_time = SDL_GetTicks();
            const float delta_time = static_cast<float>(current_frame_time - last_frame_time) / 1000.0f;
            last_frame_time = current_frame_time;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    is_game_on = false;

                if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
                {
                    if (auto inputSystem = GetCoordinator().GetSystem<InputSystem>())
                    {
                        inputSystem->OnKeyEvent(event.key.keysym.sym, event.type == SDL_KEYDOWN);
                    }
                }

                // Event hooks may register more hooks at runtime, so use a copy
                // to keep callback dispatch deterministic for the current event.
                const auto eventCallbacksSnapshot = event_callbacks;
                for (const auto& callback : eventCallbacksSnapshot)
                {
                    callback(event);
                }
            }

            SDL_SetRenderDrawColor(GetWindow().GetRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(GetWindow().GetRenderer());

            GetCoordinator().GetSystem<BaseSystem>()->Update();

            // Match event dispatch semantics: callbacks added mid-frame start on
            // the next frame instead of mutating the current iteration.
            const auto updateCallbacksSnapshot = update_callbacks;
            for (const auto& callback : updateCallbacksSnapshot)
            {
                callback(delta_time);
            }

            GetSceneManager().Update(delta_time);

            SDL_RenderPresent(GetWindow().GetRenderer());
        }

        for (const Entity entity : GetCoordinator().GetAllEntities())
        {
            GetCoordinator().DestroyEntity(entity);
        }

        GetWindow().CleanUp();
        core_initialized = false;
    }

    Coordinator& GetCoordinator()
    {
        static Coordinator instance;
        return instance;
    }

    SceneManager& GetSceneManager()
    {
        static SceneManager instance;
        return instance;
    }

    Window& GetWindow()
    {
        static Window instance;
        return instance;
    }
}
