#pragma once
#include <cmath>

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

            static constexpr float triggerEpsilon = 0.5f;
            const float triggerEpsilonSquared = triggerEpsilon * triggerEpsilon;
            for (auto &event: pathComponent.events) {
                const float dx = transformComponent.position.x - event.trigger.x;
                const float dy = transformComponent.position.y - event.trigger.y;
                const float distanceSquared = (dx * dx) + (dy * dy);

                if (!event.triggered && distanceSquared <= triggerEpsilonSquared) {
                    if (event.action) {
                        event.action(entity);
                    }
                    event.triggered = true;
                }
            }
        }
    }
};
