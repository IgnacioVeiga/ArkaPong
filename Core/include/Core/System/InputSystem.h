#pragma once
#include "Core/Core.h"
#include <unordered_set>

class InputSystem : public System {
public:
    void Init() {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<InputComponent>());
        Core::GetCoordinator().SetSystemSignature<InputSystem>(signature);
    }

    void OnKeyEvent(SDL_Keycode keycode, bool pressed) {
        if (pressed) {
            pressedKeys.insert(keycode);
        } else {
            pressedKeys.erase(keycode);
        }
    }

    void Update() {
        const Uint8 *keyStates = SDL_GetKeyboardState(nullptr);
        const Uint32 currentTime = SDL_GetTicks();

        for (auto const &entity: mEntities) {
            auto &inputComponent = Core::GetCoordinator().GetComponent<InputComponent>(entity);

            for (auto &keyMapping: inputComponent.keyMappings) {
                const Uint32 lastPressTime = inputComponent.lastKeyPressTime[keyMapping.scancode];
                const bool scancodeHit = keyMapping.scancode != SDL_SCANCODE_UNKNOWN && keyStates[keyMapping.scancode];
                const bool keycodeHit = keyMapping.keycode != SDLK_UNKNOWN &&
                                        pressedKeys.find(keyMapping.keycode) != pressedKeys.end();

                if ((scancodeHit || keycodeHit) && (currentTime - lastPressTime >= inputComponent.debounce_time)) {
                    keyMapping.keyBehavior(entity);
                    inputComponent.lastKeyPressTime[keyMapping.scancode] = currentTime;
                }
            }
        }

        if (keyStates[SDL_SCANCODE_ESCAPE]) {
            Core::is_game_on = false;
        }
    }

private:
    std::unordered_set<SDL_Keycode> pressedKeys;
};
