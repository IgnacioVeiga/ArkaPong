#pragma once

class SolidColorBackgroundSystem : public System {
public:
	void Init()
	{
		Signature signature{};
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
