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
    void Init(const nlohmann::json& config)
	{
		Signature signature{};
		signature.set(Core::coordinator.GetComponentType<BaseComponent>());
		Core::coordinator.SetSystemSignature<BaseSystem>(signature);

		Core::coordinator.RegisterComponent<InputComponent>();
		Core::coordinator.RegisterComponent<TransformComponent>();
		Core::coordinator.RegisterComponent<SpriteComponent>();
		Core::coordinator.RegisterComponent<AudioComponent>();
		Core::coordinator.RegisterComponent<TextComponent>();

		Core::coordinator.RegisterComponent<ImageBackgroundComponent>();
		Core::coordinator.RegisterComponent<ParallaxBackgroundComponent>();
		Core::coordinator.RegisterComponent<SolidColorBackgroundComponent>();
		Core::coordinator.RegisterComponent<TileBackgroundComponent>();
		
		Core::coordinator.RegisterComponent<AnimationComponent>();
		Core::coordinator.RegisterComponent<PathComponent>();
		Core::coordinator.RegisterComponent<RigidBodyComponent>();

		Core::coordinator.RegisterSystem<InputSystem>()->Init();
		Core::coordinator.RegisterSystem<SpriteSystem>()->Init();
		Core::coordinator.RegisterSystem<AudioSystem>()->Init();
		Core::coordinator.RegisterSystem<TextSystem>()->Init();

		Core::coordinator.RegisterSystem<ImageBackgroundSystem>()->Init();
		Core::coordinator.RegisterSystem<ParallaxBackgroundSystem>()->Init();
		Core::coordinator.RegisterSystem<SolidColorBackgroundSystem>()->Init();
		Core::coordinator.RegisterSystem<TileBackgroundSystem>()->Init();

		Core::coordinator.RegisterSystem<AnimationSystem>()->Init();
		Core::coordinator.RegisterSystem<PathSystem>()->Init();
		Core::coordinator.RegisterSystem<PhysicsSystem>()->Init(config);
	}

	void Update()
	{
        Core::coordinator.ProcessPendingDeletions();
	}

	void DestroyEntitiesByName(std::string entity_name)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Core::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.entity_name == entity_name)
			{
				Core::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}

	void DestroyEntitiesByScene(std::string scene_name)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Core::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.scene_name == scene_name)
			{
				Core::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}

	void DestroyEntitiesByTag(std::string tag)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Core::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.tag == tag)
			{
				Core::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}

	void DestroyEntitiesBySubTag(std::string sub_tag)
	{
		for (auto const &entity : mEntities)
		{
			auto &baseComponent = Core::coordinator.GetComponent<BaseComponent>(entity);
			if (baseComponent.sub_tag == sub_tag)
			{
				Core::coordinator.MarkEntityForDeletion(entity);
			}
		}
	}
};
