#pragma once

#include <functional>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL_scancode.h>

#include "Core/Entity/Entity.h"

struct InputBehavior {
    SDL_Scancode scancode;
    SDL_Keycode keycode;
    std::function<void(Entity self)> keyBehavior;
};

struct InputComponent {
    std::vector<InputBehavior> keyMappings;
    Uint32 debounce_time = 250;
    std::unordered_map<SDL_Scancode, Uint32> lastKeyPressTime;
};
