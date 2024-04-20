#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <SDL2/SDL.h>
#include "GameFlowManager.h"

class InputManager
{
public:
    static void handleInput(GameFlowManager &flowManager);
};

#endif
