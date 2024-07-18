#include "GameScene.h"
#include "ECS/MovementSystem.h"
#include "ECS/RenderSystem.h"
#include "Game.h"

GameScene::GameScene() {}

void GameScene::Load()
{
    systemManager.RegisterSystem<MovementSystem>();
    systemManager.RegisterSystem<RenderSystem>();
}

void GameScene::Update(float deltaTime)
{
    systemManager.UpdateSystems(deltaTime);
}

void GameScene::Render()
{
    systemManager.RenderSystems();
}
