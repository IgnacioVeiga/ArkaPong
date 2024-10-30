#pragma once

class PathSystem : public System {
public:
	void Init()
	{
		Signature signature{};
		signature.set(Game::coordinator.GetComponentType<PathComponent>());
		signature.set(Game::coordinator.GetComponentType<TransformComponent>());
		Game::coordinator.SetSystemSignature<PathSystem>(signature);
	}

	void Update(float delta_time) {
		for (auto const& entity : mEntities) {
			auto& pathComponent = Game::coordinator.GetComponent<PathComponent>(entity);
			auto& transformComponent = Game::coordinator.GetComponent<TransformComponent>(entity);

			if (pathComponent.path) {
				pathComponent.path->UpdatePosition(transformComponent.position, delta_time);
			}

			for (const auto& event : pathComponent.events) {
				if (transformComponent.position == event.trigger) {
					event.action(entity);
				}
			}
		}
	}
};