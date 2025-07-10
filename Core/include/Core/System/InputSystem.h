#pragma once
#include "Core/Core.h"

class InputSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<InputComponent>());
        Core::GetCoordinator().SetSystemSignature<InputSystem>(signature);
    }

    void Update() {
        const Uint8 *keyStates = SDL_GetKeyboardState(nullptr);
        const Uint32 currentTime = SDL_GetTicks();

        for (auto const &entity: mEntities) {
            auto &inputComponent = Core::GetCoordinator().GetComponent<InputComponent>(entity);

            for (auto &keyMapping: inputComponent.keyMappings) {
                if (const Uint32 lastPressTime = inputComponent.lastKeyPressTime[keyMapping.keyMap];
                    keyStates[keyMapping.keyMap] && (currentTime - lastPressTime >= inputComponent.debounce_time)) {
                    keyMapping.keyBehavior(entity);

                    inputComponent.lastKeyPressTime[keyMapping.keyMap] = currentTime;
                }
            }
        }

        if (keyStates[SDL_SCANCODE_ESCAPE]) {
            Core::is_game_on = false;
        }
    }
};
