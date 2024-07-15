#include "GameScene.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "PositionComponent.h"
#include "RenderComponent.h"
#include "MovementSystem.h"
#include "RenderSystem.h"

extern EntityManager entityManager;
extern SystemManager systemManager;
extern ComponentManager componentManager;

void GameScene::Load()
{
    // Crear entidades y añadir componentes
    Entity entity = entityManager.CreateEntity();
    PositionComponent position = {100.0f, 100.0f};
    componentManager.AddComponent<PositionComponent>(entity, position);

    // Añadir sistemas al SystemManager
    systemManager.RegisterSystem<MovementSystem>();
    systemManager.RegisterSystem<RenderSystem>();

    // Establecer componentes necesarios para los sistemas
    systemManager.AddComponentType<MovementSystem, PositionComponent>();
    systemManager.AddComponentType<RenderSystem, PositionComponent>();
    systemManager.AddComponentType<RenderSystem, RenderComponent>();
}

void GameScene::Update(float deltaTime)
{
    systemManager.UpdateSystems(deltaTime);
}

void GameScene::Render(SDL_Renderer *renderer)
{
    systemManager.RenderSystems(renderer);
}
