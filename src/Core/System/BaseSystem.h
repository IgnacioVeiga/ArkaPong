#pragma once

#include "../Component/InputComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Component/AudioComponent.h"
#include "../Component/TextComponent.h"
#include "../Component/Background/Background.h"
#include "../Component/AnimationComponent.h"
#include "../Component/PathComponent.h"
#include "../Component/RigidBodyComponent.h"

#include "InputSystem.h"
#include "SpriteSystem.h"
#include "AudioSystem.h"
#include "TextSystem.h"
#include "Background/Background.h"
#include "AnimationSystem.h"
#include "PathSystem.h"
#include "PhysicsSystem.h"
#include "System.h"

class BaseSystem : public System
{
public:
	void Init()
	{
		Signature signature{};
		signature.set(Game::coordinator.GetComponentType<BaseComponent>());
		Game::coordinator.SetSystemSignature<BaseSystem>(signature);

		Game::coordinator.RegisterComponent<InputComponent>();
		Game::coordinator.RegisterComponent<TransformComponent>();
		Game::coordinator.RegisterComponent<SpriteComponent>();
		Game::coordinator.RegisterComponent<AudioComponent>();
		Game::coordinator.RegisterComponent<TextComponent>();

		Game::coordinator.RegisterComponent<ImageBackgroundComponent>();
		Game::coordinator.RegisterComponent<ParallaxBackgroundComponent>();
		Game::coordinator.RegisterComponent<SolidColorBackgroundComponent>();
		Game::coordinator.RegisterComponent<TileBackgroundComponent>();
		
		Game::coordinator.RegisterComponent<AnimationComponent>();
		Game::coordinator.RegisterComponent<PathComponent>();
		Game::coordinator.RegisterComponent<RigidBodyComponent>();

		Game::coordinator.RegisterSystem<InputSystem>()->Init();
		Game::coordinator.RegisterSystem<SpriteSystem>()->Init();
		Game::coordinator.RegisterSystem<AudioSystem>()->Init();
		Game::coordinator.RegisterSystem<TextSystem>()->Init();

		Game::coordinator.RegisterSystem<ImageBackgroundSystem>()->Init();
		Game::coordinator.RegisterSystem<ParallaxBackgroundSystem>()->Init();
		Game::coordinator.RegisterSystem<SolidColorBackgroundSystem>()->Init();
		Game::coordinator.RegisterSystem<TileBackgroundSystem>()->Init();

		Game::coordinator.RegisterSystem<AnimationSystem>()->Init();
		Game::coordinator.RegisterSystem<PathSystem>()->Init();
		Game::coordinator.RegisterSystem<PhysicsSystem>()->Init();
	}

	void Update()
	{
        Game::coordinator.ProcessPendingDeletions();
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
