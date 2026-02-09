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
                const bool scancodeHit = keyMapping.scancode != SDL_SCANCODE_UNKNOWN && keyStates[keyMapping.scancode];
                const SDL_Scancode layoutScancode = keyMapping.keycode != SDLK_UNKNOWN
                                                        ? SDL_GetScancodeFromKey(keyMapping.keycode)
                                                        : SDL_SCANCODE_UNKNOWN;
                const bool layoutHit = layoutScancode != SDL_SCANCODE_UNKNOWN && keyStates[layoutScancode];

                const SDL_Scancode debounceKey = keyMapping.scancode != SDL_SCANCODE_UNKNOWN
                                                     ? keyMapping.scancode
                                                     : layoutScancode;
                const Uint32 lastPressTime = inputComponent.lastKeyPressTime[debounceKey];

                if ((scancodeHit || layoutHit) && (currentTime - lastPressTime >= inputComponent.debounce_time)) {
                    keyMapping.keyBehavior(entity);
                    inputComponent.lastKeyPressTime[debounceKey] = currentTime;
                }
            }
        }

        if (keyStates[SDL_SCANCODE_ESCAPE]) {
            Core::is_game_on = false;
        }
    }
};
