#pragma once

#include <unordered_map>
#include <string>
#include <SDL2/SDL.h>

struct InputComponent
{
    std::unordered_map<std::string, SDL_Keycode> keyMappings;
    std::unordered_map<SDL_Keycode, bool> keyStates;
};
