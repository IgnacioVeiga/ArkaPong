#pragma once

#include <memory>
#include <vector>

#include "Entity/Entity.h"
#include "Manager/EntityManager.h"
#include "Manager/ComponentManager.h"
#include "Manager/SystemManager.h"

class Coordinator
{
public:
    void Init()
    {
        // Create pointers to each manager
        mEntityManager = std::make_unique<EntityManager>();
        mComponentManager = std::make_unique<ComponentManager>();
        mSystemManager = std::make_unique<SystemManager>();
    }

    // Entity methods
    Entity CreateEntity(std::string entity_name, std::string scene_name, std::string tag = "", std::string sub_tag = "")
    {
        Entity entity = mEntityManager->CreateEntity();
        AddComponent<BaseComponent>(
            entity,
            {true,
             entity_name,
             scene_name,
             tag,
             sub_tag});
        return entity;
    }

    void DestroyEntity(Entity entity)
    {
        mEntityManager->DestroyEntity(entity);
        mComponentManager->EntityDestroyed(entity);
        mSystemManager->EntityDestroyed(entity);
    }

    void MarkEntityForDeletion(Entity entity)
    {
        entitiesToDelete.push_back(entity);
    }

    void ProcessPendingDeletions()
    {
        for (Entity entity : entitiesToDelete)
        {
            DestroyEntity(entity);
        }
        entitiesToDelete.clear();
    }

    // Component methods
    template <typename T>
    void RegisterComponent()
    {
        mComponentManager->RegisterComponent<T>();
    }

    template <typename T>
    void AddComponent(Entity entity, T component)
    {
        mComponentManager->AddComponent<T>(entity, component);
        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), true);
        mEntityManager->SetSignature(entity, signature);
        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    void RemoveComponent(Entity entity)
    {
        mComponentManager->RemoveComponent<T>(entity);
        auto signature = mEntityManager->GetSignature(entity);
        signature.set(mComponentManager->GetComponentType<T>(), false);
        mEntityManager->SetSignature(entity, signature);
        mSystemManager->EntitySignatureChanged(entity, signature);
    }

    template <typename T>
    T &GetComponent(Entity entity)
    {
        return mComponentManager->GetComponent<T>(entity);
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        return mComponentManager->GetComponentType<T>();
    }

    template <typename T>
    bool HasComponent(Entity entity)
    {
        return mComponentManager->HasComponent<T>(entity);
    }

    // System methods
    template <typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return mSystemManager->RegisterSystem<T>();
    }

    template <typename T>
    void SetSystemSignature(Signature signature)
    {
        mSystemManager->SetSignature<T>(signature);
    }

    template <typename T>
    std::shared_ptr<T> GetSystem()
    {
        return mSystemManager->GetSystem<T>();
    }

private:
    std::vector<Entity> entitiesToDelete;

    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<SystemManager> mSystemManager;
};
