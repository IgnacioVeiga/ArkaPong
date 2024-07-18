#include "Level.h"
#include "ECS/MovementSystem.h"
#include "ECS/RenderSystem.h"
#include "Game.h"

void Level::Load()
{
    systemManager.RegisterSystem<MovementSystem>();
    systemManager.RegisterSystem<RenderSystem>();
}

void Level::Update(float deltaTime)
{
    systemManager.UpdateSystems(deltaTime);
}

void Level::Render()
{
    systemManager.RenderSystems();
}
