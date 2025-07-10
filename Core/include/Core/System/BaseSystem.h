#pragma once

#include "Core/Component/InputComponent.h"
#include "Core/Component/TransformComponent.h"
#include "Core/Component/SpriteComponent.h"
#include "Core/Component/AudioComponent.h"
#include "Core/Component/TextComponent.h"
#include "Core/Component/Background/Background.h"
#include "Core/Component/AnimationComponent.h"
#include "Core/Component/PathComponent.h"
#include "Core/Component/RigidBodyComponent.h"

#include "InputSystem.h"
#include "SpriteSystem.h"
#include "AudioSystem.h"
#include "TextSystem.h"
#include "Background/Background.h"
#include "AnimationSystem.h"
#include "PathSystem.h"
#include "PhysicsSystem.h"
#include "System.h"

class BaseSystem : public System {
public:
    void Init(const nlohmann::json &config) {
        Signature signature{};
        signature.set(Core::GetCoordinator().GetComponentType<BaseComponent>());
        Core::GetCoordinator().SetSystemSignature<BaseSystem>(signature);

        Core::GetCoordinator().RegisterComponent<InputComponent>();
        Core::GetCoordinator().RegisterComponent<TransformComponent>();
        Core::GetCoordinator().RegisterComponent<SpriteComponent>();
        Core::GetCoordinator().RegisterComponent<AudioComponent>();
        Core::GetCoordinator().RegisterComponent<TextComponent>();

        Core::GetCoordinator().RegisterComponent<ImageBackgroundComponent>();
        Core::GetCoordinator().RegisterComponent<ParallaxBackgroundComponent>();
        Core::GetCoordinator().RegisterComponent<SolidColorBackgroundComponent>();
        Core::GetCoordinator().RegisterComponent<TileBackgroundComponent>();

        Core::GetCoordinator().RegisterComponent<AnimationComponent>();
        Core::GetCoordinator().RegisterComponent<PathComponent>();
        Core::GetCoordinator().RegisterComponent<RigidBodyComponent>();

        Core::GetCoordinator().RegisterSystem<InputSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<SpriteSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<AudioSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<TextSystem>()->Init();

        Core::GetCoordinator().RegisterSystem<ImageBackgroundSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<ParallaxBackgroundSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<SolidColorBackgroundSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<TileBackgroundSystem>()->Init();

        Core::GetCoordinator().RegisterSystem<AnimationSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<PathSystem>()->Init();
        Core::GetCoordinator().RegisterSystem<PhysicsSystem>()->Init(config);
    }

    void Update() {
        Core::GetCoordinator().ProcessPendingDeletions();
    }

    void DestroyEntitiesByName(std::string entity_name) {
        for (auto const &entity: mEntities) {
            auto &baseComponent = Core::GetCoordinator().GetComponent<BaseComponent>(entity);
            if (baseComponent.entity_name == entity_name) {
                Core::GetCoordinator().MarkEntityForDeletion(entity);
            }
        }
    }

    void DestroyEntitiesByScene(std::string scene_name) {
        for (auto const &entity: mEntities) {
            auto &baseComponent = Core::GetCoordinator().GetComponent<BaseComponent>(entity);
            if (baseComponent.scene_name == scene_name) {
                Core::GetCoordinator().MarkEntityForDeletion(entity);
            }
        }
    }

    void DestroyEntitiesByTag(std::string tag) {
        for (auto const &entity: mEntities) {
            auto &baseComponent = Core::GetCoordinator().GetComponent<BaseComponent>(entity);
            if (baseComponent.tag == tag) {
                Core::GetCoordinator().MarkEntityForDeletion(entity);
            }
        }
    }

    void DestroyEntitiesBySubTag(std::string sub_tag) {
        for (auto const &entity: mEntities) {
            auto &baseComponent = Core::GetCoordinator().GetComponent<BaseComponent>(entity);
            if (baseComponent.sub_tag == sub_tag) {
                Core::GetCoordinator().MarkEntityForDeletion(entity);
            }
        }
    }
};
