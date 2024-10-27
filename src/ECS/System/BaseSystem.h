#pragma once

#include <SDL2/SDL.h>
#include "../../Game.h"
#include "../Coordinator.h"
#include "../System/System.h"
#include "../System/InputSystem.h"
#include "../System/MovementSystem.h"
#include "../System/SpriteSystem.h"
#include "../System/AudioSystem.h"
#include "../System/TextSystem.h"
#include "../System/CollisionSystem.h"
#include "../System/Background/TileBackgroundSystem.h"
#include "../System/Background/SolidColorBackgroundSystem.h"
#include "../System/AnimationSystem.h"
#include "../System/PathSystem.h"

class BaseSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<BaseComponent>());
		Game::coordinator.SetSystemSignature<BaseSystem>(signature);

		Game::coordinator.RegisterComponent<InputComponent>();
		Game::coordinator.RegisterComponent<TransformComponent>();
		Game::coordinator.RegisterComponent<VelocityComponent>();
		Game::coordinator.RegisterComponent<SpriteComponent>();
		Game::coordinator.RegisterComponent<AudioComponent>();
		Game::coordinator.RegisterComponent<TextComponent>();
		Game::coordinator.RegisterComponent<CollisionComponent>();
		Game::coordinator.RegisterComponent<TileBackgroundComponent>();
		Game::coordinator.RegisterComponent<SolidColorBackgroundComponent>();
		Game::coordinator.RegisterComponent<AnimationComponent>();
		Game::coordinator.RegisterComponent<PathComponent>();

		Game::coordinator.RegisterSystem<InputSystem>()->Init();
		Game::coordinator.RegisterSystem<MovementSystem>()->Init();
		Game::coordinator.RegisterSystem<SpriteSystem>()->Init();
		Game::coordinator.RegisterSystem<AudioSystem>()->Init();
		Game::coordinator.RegisterSystem<TextSystem>()->Init();
		Game::coordinator.RegisterSystem<CollisionSystem>()->Init();
		Game::coordinator.RegisterSystem<TileBackgroundSystem>()->Init();
		Game::coordinator.RegisterSystem<SolidColorBackgroundSystem>()->Init();
		Game::coordinator.RegisterSystem<AnimationSystem>()->Init();
		Game::coordinator.RegisterSystem<PathSystem>()->Init();
	}

	void Update(float deltaTime)
	{
        Game::coordinator.ProcessPendingDeletions();

		Game::coordinator.GetSystem<InputSystem>()->Update();
		Game::coordinator.GetSystem<MovementSystem>()->Update(deltaTime);
		Game::coordinator.GetSystem<TileBackgroundSystem>()->Update();
		Game::coordinator.GetSystem<SolidColorBackgroundSystem>()->Update();
		Game::coordinator.GetSystem<SpriteSystem>()->Update();
		Game::coordinator.GetSystem<AudioSystem>()->Update();
		Game::coordinator.GetSystem<TextSystem>()->Update();
		Game::coordinator.GetSystem<CollisionSystem>()->Update();
		Game::coordinator.GetSystem<AnimationSystem>()->Update();
		Game::coordinator.GetSystem<PathSystem>()->Update();
	}

	void DestroyEntitiesByName(std::string entity_name)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Game::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.entity_name == entity_name)
			{
				Game::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}

	void DestroyEntitiesByScene(std::string scene_name)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Game::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.scene_name == scene_name)
			{
				Game::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}

	void DestroyEntitiesByTag(std::string tag)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Game::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.tag == tag)
			{
				Game::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}

	void DestroyEntitiesBySubTag(std::string sub_tag)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Game::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.sub_tag == sub_tag)
			{
				Game::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}
};
