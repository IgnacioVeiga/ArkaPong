#include "Core/Utils/Coordinator.h"

void Coordinator::Init()
{
    // Create pointers to each manager
    mEntityManager = std::make_unique<EntityManager>();
    mComponentManager = std::make_unique<ComponentManager>();
    mSystemManager = std::make_unique<SystemManager>();
}

// Entity methods
Entity Coordinator::CreateEntity(const std::string &entity_name,
                                 const std::string &scene_name,
                                 const std::string &tag,
                                 const std::string &sub_tag)
{
    const Entity entity = mEntityManager->CreateEntity();
    AddComponent<BaseComponent>(
        entity,
        {true,
         entity_name,
         scene_name,
         tag,
         sub_tag});
    return entity;
}

void Coordinator::DestroyEntity(const Entity entity) const
{
    mEntityManager->DestroyEntity(entity);
    mComponentManager->EntityDestroyed(entity);
    mSystemManager->EntityDestroyed(entity);
}

void Coordinator::MarkEntityForDeletion(const Entity entity)
{
    entitiesToDelete.push_back(entity);
}

void Coordinator::ProcessPendingDeletions()
{
    for (const Entity entity : entitiesToDelete)
    {
        DestroyEntity(entity);
    }
    entitiesToDelete.clear();
}

bool Coordinator::EntityExists(Entity entity) const
{
    return mEntityManager->EntityExists(entity);
}

std::vector<Entity> Coordinator::GetAllEntities() const
{
    return mEntityManager->GetAllEntities();
}

nlohmann::json Coordinator::SerializeEntity(Entity e)
{
    nlohmann::json j;

    if (!EntityExists(e))
    {
        j["error"] = "entity not found";
        return j;
    }

    // BaseComponent as an example of serialization
    if (HasComponent<BaseComponent>(e))
    {
        const auto &base = GetComponent<BaseComponent>(e);
        j["BaseComponent"] = {
            {"active", base.active},
            {"entity_name", base.entity_name},
            {"scene_name", base.scene_name},
            {"tag", base.tag},
            {"sub_tag", base.sub_tag}};
    }

    // TODO: Repeat this for other registered components
    return j;
}

Entity Coordinator::DeserializeEntity(const nlohmann::json &j)
{
    if (!j.contains("BaseComponent"))
        throw std::runtime_error("Invalid JSON: missing BaseComponent");

    const auto &base = j["BaseComponent"];

    Entity e = CreateEntity(
        base.value("entity_name", "Unnamed"),
        base.value("scene_name", "Default"),
        base.value("tag", "Untagged"),
        base.value("sub_tag", ""));

    // Assign values to the component
    if (HasComponent<BaseComponent>(e))
    {
        auto &comp = GetComponent<BaseComponent>(e);
        comp.active = base.value("active", true);
        comp.entity_name = base.value("entity_name", "");
        comp.scene_name = base.value("scene_name", "");
        comp.tag = base.value("tag", "");
        comp.sub_tag = base.value("sub_tag", "");
    }

    // TODO: Repeat this for other registered components
    return e;
}

std::vector<std::string> Coordinator::GetComponentsOfEntity(Entity entity) const
{
    std::vector<std::string> result;
    for (auto &[typeName, array] : mComponentManager->GetAllComponentArrays())
    {
        if (array->HasData(entity))
        {
            result.push_back(typeName);
        }
    }
    return result;
}