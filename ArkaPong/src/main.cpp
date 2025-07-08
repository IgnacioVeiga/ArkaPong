#define SDL_MAIN_HANDLED

#include <chrono>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>

#include "Core/Core.h"
#include "Core/Utils/Configuration.h"
#include "Core/Component/BaseComponent.h"
#include "Core/System/BaseSystem.h"

#include "Scenes/MainMenuScene.h"
#include "Scenes/GameScene.h"

int main(int argc, char *argv[]) {
    srand(static_cast<Uint32>(time(nullptr)));

    json config = readConfig();
    const json defaultConfig = getDefaultConfig();
    mergeConfig(config, defaultConfig);
    std::cout << config.dump(4) << std::endl;

    if (!Core::GetWindow().Init(DEFAULT_GAME_TITLE))
        return 1;

    Core::GetCoordinator().Init();
    Core::GetCoordinator().RegisterComponent<BaseComponent>();
    Core::GetCoordinator().RegisterSystem<BaseSystem>()->Init(config);

    Core::GetSceneManager().Add(TITLE_SCENE, std::make_unique<MainMenuScene>());
    Core::GetSceneManager().Add(ROUND_SCENE, std::make_unique<GameScene>());
    Core::GetSceneManager().Init(TITLE_SCENE);

    Uint32 last_frame_time = SDL_GetTicks();
    SDL_Event event;

    while (Core::is_game_on) {
        const Uint32 current_frame_time = SDL_GetTicks();
        const float delta_time = static_cast<float_t>(current_frame_time - last_frame_time) / 1000;
        last_frame_time = current_frame_time;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                Core::is_game_on = false;
        }

        SDL_SetRenderDrawColor(Core::GetWindow().GetRenderer(), 0, 0, 0, 255);
        SDL_RenderClear(Core::GetWindow().GetRenderer());

        Core::GetCoordinator().GetSystem<BaseSystem>()->Update();
        Core::GetSceneManager().Update(delta_time);

        SDL_RenderPresent(Core::GetWindow().GetRenderer());
    }

    Core::GetWindow().CleanUp();
    return 0;
}
