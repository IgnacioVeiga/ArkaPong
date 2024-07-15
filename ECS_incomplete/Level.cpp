#include "Level.h"
#include "SystemManager.h"

extern SystemManager systemManager;

void Level::Update(float deltaTime)
{
    systemManager.UpdateSystems(deltaTime);
}

void Level::Render(SDL_Renderer *renderer)
{
    systemManager.RenderSystems(renderer);
}
