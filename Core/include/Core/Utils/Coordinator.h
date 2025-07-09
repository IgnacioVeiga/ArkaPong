#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../Entity/Entity.h"
#include "../Component/BaseComponent.h"
#include "../Manager/EntityManager.h"
#include "../Manager/ComponentManager.h"
#include "../Manager/SystemManager.h"

class Coordinator {
public:
    void Init() {
        // Create pointers to each manager
        mEntityManager = std::make_unique<EntityManager>();
        mComponentManager = std::make_unique<ComponentManager>();
        mSystemManager = std::make_unique<SystemManager>();
    }

    // Entity methods
    Entity CreateEntity(const std::string &entity_name,
                        const std::string &scene_name,
                        const std::string &tag = "",
                        const std::string &sub_tag = ""
    ) {
        const Entity entity = mEntityManager->CreateEntity();
        AddComponent<BaseComponent>(
            entity,
            {
                true,
                entity_name,
                scene_name,
                tag,
                sub_tag
            });
        return entity;
    }

    void DestroyEntity(const Entity entity) const {
        mEntityManager->DestroyEntity(entity);
        mComponentManager->EntityDestroyed(entity);
        mSystemManager->EntityDestroyed(entity);
    }

    void MarkEntityForDeletion(const Entity entity) {
        entitiesToDelete.push_back(entity);
    }

    void ProcessPendingDeletions() {
        for (const Entity entity: entitiesToDelete) {
            DestroyEntity(entity);
        }
        entitiesToDelete.clear();
    }

    // Component methods
    template<typename T>
    void RegisterComponent() const {
        mComponentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(const Entity entity, T component) {
        mComponentManager->AddComponent<T>(entity, std::move(component));
        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), true);
        mEntityManager->SetSignature(entity, signature);
        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(const Entity entity) const {
        mComponentManager->RemoveComponent<T>(entity);
        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), false);
        mEntityManager->SetSignature(entity, signature);
        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T &GetComponent(const Entity entity) {
        return mComponentManager->GetComponent<T>(entity);
    }

    template<typename T>
    [[nodiscard]] ComponentType GetComponentType() const {
        return mComponentManager->GetComponentType<T>();
    }

    template<typename T>
    [[nodiscard]] bool HasComponent(const Entity entity) const {
        return mComponentManager->HasComponent<T>(entity);
    }

    // System methods
    template<typename T>
    std::shared_ptr<T> RegisterSystem() {
        return mSystemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(const Signature signature) const {
        mSystemManager->SetSignature<T>(signature);
    }

    template<typename T>
    std::shared_ptr<T> GetSystem() {
        return mSystemManager->GetSystem<T>();
    }

private:
    std::vector<Entity> entitiesToDelete;

    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<SystemManager> mSystemManager;
};
