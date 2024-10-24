#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../System/System.h"
#include "../Coordinator.h"
#include "../Component/InputComponent.h"

class InputSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<InputComponent>());
		Game::coordinator.SetSystemSignature<InputSystem>(signature);
	}

	void Update()
	{
		const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
		Uint32 currentTime = SDL_GetTicks();

		for (auto const &entity : mEntities)
		{
			auto &inputComponent = Game::coordinator.GetComponent<InputComponent>(entity);

			for (auto &keyMapping : inputComponent.keyMappings)
			{
				Uint32 lastPressTime = inputComponent.lastKeyPressTime[keyMapping.keyMap];
				if (keyStates[keyMapping.keyMap] && (currentTime - lastPressTime >= DEBOUNCE_TIME))
				{
					keyMapping.keyBehavior(entity);

					inputComponent.lastKeyPressTime[keyMapping.keyMap] = currentTime;
				}
			}
		}

		if (keyStates[SDL_SCANCODE_ESCAPE])
		{
			Game::game_on = false;
		}
	}
};
