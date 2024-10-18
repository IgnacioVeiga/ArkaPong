#pragma once

#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/PathComponent.h"
#include <chrono>

class PathSystem : public System {
public:
	void Init() {
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<PathComponent>());
		signature.set(Game::coordinator.GetComponentType<PositionComponent>());
		Game::coordinator.SetSystemSignature<PathSystem>(signature);
	}

	void Update() {
		using namespace std::chrono;
		// Get the current time
		auto now = steady_clock::now();
		// Calculate the deltaTime
		static auto lastTime = now;
		float deltaTime = duration_cast<duration<float>>(now - lastTime).count();
		lastTime = now;

		for (auto const& entity : mEntities) {
			auto& pathComponent = Game::coordinator.GetComponent<PathComponent>(entity);
			auto& positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);

			if (pathComponent.path) {
				pathComponent.path->UpdatePosition(positionComponent.x, positionComponent.y, deltaTime);
			}

			for (const auto& event : pathComponent.events) {
				if (positionComponent.x == event.triggerX && positionComponent.y == event.triggerY) {
					event.action(entity);
				}
			}
		}
	}
};