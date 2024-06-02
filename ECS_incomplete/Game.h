#pragma once

#include <SDL2/SDL_render.h>
#include <vector>
#include "EntityManager.h"
#include "ComponentManager.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "RenderSystem.h"
#include "Components.h"

class Game
{
public:
    Game();
    ~Game();
    void run();
    static SDL_Renderer *renderer;
    static bool game_on;

private:
    void initSDL();
    void initECS();
    void cleanUp();
    static SDL_Window *window;

    EntityManager entityManager;
    ComponentManager componentManager;
    InputSystem inputSystem;
    MovementSystem movementSystem;
    RenderSystem renderSystem;
    std::vector<std::pair<PositionComponent, RenderComponent>> entities;
};
