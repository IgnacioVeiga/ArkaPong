#define SDL_MAIN_HANDLED

#include <stdlib.h>
#include <chrono>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_render.h>

#include "Core/Game.h"
#include "Core/Component/BaseComponent.h"
#include "Core/System/BaseSystem.h"
#include "Game/Scenes/MainMenuScene.h"
#include "Game/Scenes/GameScene.h"

bool Init()
{
	if (!Game::window.Init())
		return false;

	Game::coordinator.Init();
	Game::coordinator.RegisterComponent<BaseComponent>();
	Game::coordinator.RegisterSystem<BaseSystem>()->Init();
	return true;
}

void Run()
{
	Game::scene_manager.Add("MainMenu", std::make_unique<MainMenuScene>());
	Game::scene_manager.Add("Game", std::make_unique<GameScene>());
	Game::scene_manager.Init("MainMenu");

	const int FPS = 60;
	// target time per frame in milliseconds
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	Uint32 frameTime;

	SDL_Event event;
	while (Game::game_on)
	{
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				Game::game_on = false;
			}
		}

		frameTime = SDL_GetTicks() - frameStart;
		// TODO: fix this
		// float delta_time = frameTime / 1000.0f;
		float delta_time = 1.0f;

		SDL_SetRenderDrawColor(Game::window.GetRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(Game::window.GetRenderer());

		Game::scene_manager.Update(delta_time);

		SDL_RenderPresent(Game::window.GetRenderer());

		// SDL_Delay() is used to wait only if the current frame has completed faster than expected.
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
	}
}

void CleanUp()
{
	Game::window.CleanUp();
}

int main(int argc, char* argv[])
{
	srand(time(nullptr));

	if (!Init()) return 1;

	Run();
	CleanUp();

	return 0;
}