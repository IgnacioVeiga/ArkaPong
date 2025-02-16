#pragma once

#include <functional>
#include <SDL2/SDL_keycode.h>
#include "../Entity/Entity.h"

struct InputBehavior
{
	SDL_Keycode keyMap;
	std::function<void(Entity self)> keyBehavior;
};

struct InputComponent
{
	std::vector<InputBehavior> keyMappings;
	Uint32 debounce_time = 250;
	std::unordered_map<SDL_Keycode, Uint32> lastKeyPressTime;
};