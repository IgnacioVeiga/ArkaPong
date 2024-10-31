#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <chrono>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>

#include "Core/Game.h"
#include "Core/Component/BaseComponent.h"
#include "Core/System/BaseSystem.h"

#include "ArkaPong/Scenes/MainMenuScene.h"
#include "ArkaPong/Scenes/GameScene.h"

static bool Init()
{
	if (!Game::window.Init(GAME_TITLE))
		return false;

	Game::coordinator.Init();
	Game::coordinator.RegisterComponent<BaseComponent>();
	Game::coordinator.RegisterSystem<BaseSystem>()->Init();

	Game::scene_manager.Add("MainMenu", std::make_unique<MainMenuScene>());
	Game::scene_manager.Add("Game", std::make_unique<GameScene>());
	Game::scene_manager.Init("MainMenu");
	return true;
}

static void Run()
{
	Uint32 last_frame_time = SDL_GetTicks();
	float delta_time;

	SDL_Event event;
	while (Game::game_on)
	{
		Uint32 current_frame_time = SDL_GetTicks();
		delta_time = (current_frame_time - last_frame_time) / 1000.0f;
		last_frame_time = current_frame_time;

		if (delta_time <= 0) delta_time = 0.001f;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) Game::game_on = false;
		}

		SDL_SetRenderDrawColor(Game::window.GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Game::window.GetRenderer());

		Game::coordinator.GetSystem<BaseSystem>()->Update();
		Game::scene_manager.Update(delta_time);

		SDL_RenderPresent(Game::window.GetRenderer());
	}
}

int main(int argc, char *argv[])
{
	srand(static_cast<Uint32>(time(nullptr)));

	if (!Init())
		return 1;

	Run();
	Game::window.CleanUp();

	return 0;
}