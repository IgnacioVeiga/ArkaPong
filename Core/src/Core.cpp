#include "Core/Core.h"
#include "Core/Utils/Configuration.h"
#include "Core/Utils/Window.h"
#include "Core/Manager/SceneManager.h"
#include "Core/System/BaseSystem.h"
#include "Core/Component/BaseComponent.h"
#include <cstdlib>
#include <ctime>

namespace Core
{
    bool is_game_on = true;
    json config;

    void Init(const std::string& config_path, const char* title)
    {
        srand(static_cast<Uint32>(time(nullptr)));

        config = readConfig(config_path);
        mergeConfig(config, getDefaultConfig());
        std::cout << config.dump(4) << std::endl;

        if (!GetWindow().Init(title))
        {
            is_game_on = false;
            return;
        }

        GetCoordinator().Init();
        GetCoordinator().RegisterComponent<BaseComponent>();
        GetCoordinator().RegisterSystem<BaseSystem>()->Init(config);
    }

    void Run()
    {
        Uint32 last_frame_time = SDL_GetTicks();
        SDL_Event event;

        while (is_game_on)
        {
            const Uint32 current_frame_time = SDL_GetTicks();
            const float delta_time = (current_frame_time - last_frame_time) / 1000.0f;
            last_frame_time = current_frame_time;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    is_game_on = false;
            }

            SDL_SetRenderDrawColor(GetWindow().GetRenderer(), 0, 0, 0, 255);
            SDL_RenderClear(GetWindow().GetRenderer());

            GetCoordinator().GetSystem<BaseSystem>()->Update();
            GetSceneManager().Update(delta_time);

            SDL_RenderPresent(GetWindow().GetRenderer());
        }
    }

    void CleanUp()
    {
        GetWindow().CleanUp();
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
