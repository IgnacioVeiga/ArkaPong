#pragma once

#include "Entity.h"
#include "Components.h"
#include <SDL2/SDL_keyboard.h>

class InputSystem
{
public:
    void update(ComponentManager &componentManager)
    {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        for (auto &entity : entities)
        {
            auto *input = componentManager.getComponent<InputComponent>(entity.getId());
            auto *velocity = componentManager.getComponent<VelocityComponent>(entity.getId());

            if (input && velocity)
            {
                if (keystate[input->upKey])
                {
                    velocity->y = -1;
                }
                else if (keystate[input->downKey])
                {
                    velocity->y = 1;
                }
                else
                {
                    velocity->y = 0;
                }
            }
        }
    }

    void addEntity(Entity entity)
    {
        entities.push_back(entity);
    }

private:
    std::vector<Entity> entities;
};
