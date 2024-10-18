#pragma once

#include "../../../Game.h"
#include "../../Coordinator.h"
#include "../../Component/Background/SolidColorBackgroundComponent.h"

/*
	Example of how to use:
	Entity solidColorBackground = CreateSolidColorBackgroundEntity(C_BLACK);
*/
class SolidColorBackgroundSystem : public System {
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<SolidColorBackgroundComponent>());
		Game::coordinator.SetSystemSignature<SolidColorBackgroundSystem>(signature);
	}

	void Update() {
		for (auto const& entity : mEntities) {
			auto& bg = Game::coordinator.GetComponent<SolidColorBackgroundComponent>(entity);
			SDL_SetRenderDrawColor(Game::window.GetRenderer(), bg.color.r, bg.color.g, bg.color.b, bg.color.a);
			SDL_RenderClear(Game::window.GetRenderer());
		}
	}
};
