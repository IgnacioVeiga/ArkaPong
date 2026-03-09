#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "../Entity/Entity.h"
#include "../Component/BaseComponent.h"
#include "../Manager/EntityManager.h"
#include "../Manager/ComponentManager.h"
#include "../Manager/SystemManager.h"
#include "Core/CoreExport.h"
#include "nlohmann-json/json.hpp"

class CORE_API Coordinator {
public:
    void Init();

    // Entity methods
    Entity CreateEntity(const std::string &entity_name,
                        const std::string &scene_name,
                        const std::string &tag = "",
                        const std::string &sub_tag = "");
    void DestroyEntity(const Entity entity);
    void MarkEntityForDeletion(const Entity entity);
    void ProcessPendingDeletions();
    bool EntityExists(Entity entity) const;
    std::vector<Entity> GetAllEntities() const;
    std::vector<Entity> GetEntitiesByScene(const std::string& scene_name);
    nlohmann::json SerializeEntity(Entity entity);
    Entity DeserializeEntity(const nlohmann::json& j);
    nlohmann::json SerializeScene(const std::string& scene_name);
    std::vector<Entity> DeserializeScene(
        const nlohmann::json& j,
        const std::string& override_scene_name = "",
        bool clear_existing_scene = false);
    bool SaveSceneToFile(const std::string& scene_name, const std::string& path);
    std::vector<Entity> LoadSceneFromFile(
        const std::string& path,
        const std::string& override_scene_name = "",
        bool clear_existing_scene = false);

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

    std::vector<std::string> GetComponentsOfEntity(Entity entity) const;
private:
    std::vector<Entity> entitiesToDelete;

    std::unique_ptr<EntityManager> mEntityManager;
    std::unique_ptr<ComponentManager> mComponentManager;
    std::unique_ptr<SystemManager> mSystemManager;
};
