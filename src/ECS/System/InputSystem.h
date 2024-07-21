#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../System/System.h"
#include "../Coordinator.h"
#include "../Component/InputComponent.h"

extern Coordinator gCoordinator;

class InputSystem : public System
{
public:
    void Init() {}

    void Update()
    {
        const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
        for (auto const &entity : mEntities)
        {
            if (gCoordinator.HasComponent<InputComponent>(entity))
            {
                auto &inputComponent = gCoordinator.GetComponent<InputComponent>(entity);
                for (auto &keyMapping : inputComponent.keyMappings)
                {
                    inputComponent.keyStates[keyMapping.second] = keyStates[keyMapping.second];
                }
            }
        }
    }
};
