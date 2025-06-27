#pragma once

class SolidColorBackgroundSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::coordinator.GetComponentType<SolidColorBackgroundComponent>());
        Core::coordinator.SetSystemSignature<SolidColorBackgroundSystem>(signature);
    }

    void Update() {
        for (auto const &entity: mEntities) {
            auto &bg = Core::coordinator.GetComponent<SolidColorBackgroundComponent>(entity);
            SDL_SetRenderDrawColor(Core::window.GetRenderer(), bg.color.r, bg.color.g, bg.color.b, bg.color.a);
            SDL_RenderClear(Core::window.GetRenderer());
        }
    }
};
