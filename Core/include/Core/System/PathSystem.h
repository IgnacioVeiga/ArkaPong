#pragma once

class PathSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<PathComponent>());
        signature.set(Core::GetCoordinator().GetComponentType<TransformComponent>());
        Core::GetCoordinator().SetSystemSignature<PathSystem>(signature);
    }

    void Update(const float delta_time) {
        for (auto const &entity: mEntities) {
            auto &pathComponent = Core::GetCoordinator().GetComponent<PathComponent>(entity);
            auto &transformComponent = Core::GetCoordinator().GetComponent<TransformComponent>(entity);

            if (pathComponent.path) {
                pathComponent.path->UpdatePosition(transformComponent.position, delta_time);
            }

            for (const auto &event: pathComponent.events) {
                if (transformComponent.position == event.trigger) {
                    event.action(entity);
                }
            }
        }
    }
};
