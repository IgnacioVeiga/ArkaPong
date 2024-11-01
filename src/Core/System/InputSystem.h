#pragma once

class InputSystem : public System
{
public:
	void Init()
	{
		Signature signature{};
		signature.set(Core::coordinator.GetComponentType<InputComponent>());
		Core::coordinator.SetSystemSignature<InputSystem>(signature);
	}

	void Update()
	{
		const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
		Uint32 currentTime = SDL_GetTicks();

		for (auto const &entity : mEntities)
		{
			auto &inputComponent = Core::coordinator.GetComponent<InputComponent>(entity);

			for (auto &keyMapping : inputComponent.keyMappings)
			{
				Uint32 lastPressTime = inputComponent.lastKeyPressTime[keyMapping.keyMap];
				if (keyStates[keyMapping.keyMap] && (currentTime - lastPressTime >= inputComponent.debounce_time))
				{
					keyMapping.keyBehavior(entity);

					inputComponent.lastKeyPressTime[keyMapping.keyMap] = currentTime;
				}
			}
		}

		if (keyStates[SDL_SCANCODE_ESCAPE])
		{
			Core::game_on = false;
		}
	}
};
