#pragma once

class PathSystem : public System {
public:
	void Init()
	{
		Signature signature{};
		signature.set(Core::coordinator.GetComponentType<PathComponent>());
		signature.set(Core::coordinator.GetComponentType<TransformComponent>());
		Core::coordinator.SetSystemSignature<PathSystem>(signature);
	}

	void Update(float delta_time) {
		for (auto const& entity : mEntities) {
			auto& pathComponent = Core::coordinator.GetComponent<PathComponent>(entity);
			auto& transformComponent = Core::coordinator.GetComponent<TransformComponent>(entity);

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