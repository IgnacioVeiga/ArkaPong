#pragma once

#include <functional>

struct InputBehavior
{
	SDL_Keycode keyMap;
	std::function<void(Entity self)> keyBehavior;
};

struct InputComponent
{
	std::vector<InputBehavior> keyMappings;
	int debounce_time = 250;
	std::unordered_map<SDL_Keycode, Uint32> lastKeyPressTime;
};