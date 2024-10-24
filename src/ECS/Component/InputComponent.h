#pragma once

#include <SDL2/SDL.h>

struct InputBehavior
{
	SDL_Keycode keyMap;
	std::function<void(Entity self)> keyBehavior;
};

struct InputComponent
{
	std::vector<InputBehavior> keyMappings;
	std::unordered_map<SDL_Keycode, Uint32> lastKeyPressTime;
};