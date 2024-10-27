#pragma once

#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/TransformComponent.h"
#include "../Component/PathComponent.h"
#include <chrono>

class PathSystem : public System {
public:
	void Init() {
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<PathComponent>());
		signature.set(Game::coordinator.GetComponentType<TransformComponent>());
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
			auto& transformComponent = Game::coordinator.GetComponent<TransformComponent>(entity);

			if (pathComponent.path) {
				pathComponent.path->UpdatePosition(transformComponent.position.x, transformComponent.position.y, deltaTime);
			}

			for (const auto& event : pathComponent.events) {
				if (transformComponent.position.x == event.triggerX && transformComponent.position.y == event.triggerY) {
					event.action(entity);
				}
			}
		}
	}
};