#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL2/SDL.h>
#include "FlowManager.h"

class InputManager
{
public:
    static void handleInput(FlowManager &flowManager);
};

#endif
