#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <chrono>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>

#include "Core/Core.h"
#include "Core/Utils/Configuration.h"
#include "Core/Component/BaseComponent.h"
#include "Core/System/BaseSystem.h"

#include "ArkaPong/Scenes/MainMenuScene.h"
#include "ArkaPong/Scenes/GameScene.h"

int main(int argc, char *argv[])
{
	srand(static_cast<Uint32>(time(nullptr)));

	json config = readConfig();
	json defaultConfig = getDefaultConfig();
	mergeConfig(config, defaultConfig);
	std::cout << config.dump(4) << std::endl;

	if (!Core::window.Init(DEFAULT_GAME_TITLE))
		return 1;

	Core::coordinator.Init();
	Core::coordinator.RegisterComponent<BaseComponent>();
	Core::coordinator.RegisterSystem<BaseSystem>()->Init(config);

	Core::scene_manager.Add(TITLE_SCENE, std::make_unique<MainMenuScene>());
	Core::scene_manager.Add(ROUND_SCENE, std::make_unique<GameScene>());
	Core::scene_manager.Init(TITLE_SCENE);

	Uint32 last_frame_time = SDL_GetTicks();
	float delta_time;
	SDL_Event event;

	while (Core::game_on)
	{
		Uint32 current_frame_time = SDL_GetTicks();
		delta_time = (current_frame_time - last_frame_time) / 1000.0f;
		last_frame_time = current_frame_time;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				Core::game_on = false;
		}

		SDL_SetRenderDrawColor(Core::window.GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Core::window.GetRenderer());

		Core::coordinator.GetSystem<BaseSystem>()->Update();
		Core::scene_manager.Update(delta_time);

		SDL_RenderPresent(Core::window.GetRenderer());
	}

	Core::window.CleanUp();
	return 0;
}