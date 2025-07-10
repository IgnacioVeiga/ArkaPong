#pragma once

class SolidColorBackgroundSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<SolidColorBackgroundComponent>());
        Core::GetCoordinator().SetSystemSignature<SolidColorBackgroundSystem>(signature);
    }

    void Update() {
        for (auto const &entity: mEntities) {
            auto &bg = Core::GetCoordinator().GetComponent<SolidColorBackgroundComponent>(entity);
            SDL_SetRenderDrawColor(Core::GetWindow().GetRenderer(), bg.color.r, bg.color.g, bg.color.b, bg.color.a);
            SDL_RenderClear(Core::GetWindow().GetRenderer());
        }
    }
};
