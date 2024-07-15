#pragma once
#include <unordered_map>
#include <memory>
#include <array>
#include <stdexcept>
#include "Entity.h"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template <typename T>
class ComponentArray : public IComponentArray
{
public:
    void InsertData(Entity entity, T component)
    {
        if (entityToIndexMap.find(entity) != entityToIndexMap.end())
        {
            throw std::runtime_error("Component added to same entity more than once.");
        }
        size_t newIndex = size;
        entityToIndexMap[entity] = newIndex;
        indexToEntityMap[newIndex] = entity;
        componentArray[newIndex] = component;
        ++size;
    }

    void RemoveData(Entity entity)
    {
        if (entityToIndexMap.find(entity) == entityToIndexMap.end())
        {
            throw std::runtime_error("Removing non-existent component.");
        }
        size_t indexOfRemovedEntity = entityToIndexMap[entity];
        size_t indexOfLastElement = size - 1;
        componentArray[indexOfRemovedEntity] = componentArray[indexOfLastElement];

        Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
        entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        entityToIndexMap.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);
        --size;
    }

    T &GetData(Entity entity)
    {
        if (entityToIndexMap.find(entity) == entityToIndexMap.end())
        {
            throw std::runtime_error("Retrieving non-existent component.");
        }
        return componentArray[entityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override
    {
        if (entityToIndexMap.find(entity) != entityToIndexMap.end())
        {
            RemoveData(entity);
        }
    }

private:
    std::array<T, MAX_ENTITIES> componentArray{};
    std::unordered_map<Entity, size_t> entityToIndexMap{};
    std::unordered_map<size_t, Entity> indexToEntityMap{};
    size_t size{};
};

class ComponentManager
{
public:
    template <typename T>
    void RegisterComponent()
    {
        const char *typeName = typeid(T).name();
        componentTypes[typeName] = nextComponentType++;
        componentArrays[typeName] = std::make_shared<ComponentArray<T>>();
    }

    template <typename T>
    ComponentType GetComponentType()
    {
        const char *typeName = typeid(T).name();
        return componentTypes[typeName];
    }

    template <typename T>
    void AddComponent(Entity entity, T component)
    {
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template <typename T>
    void RemoveComponent(Entity entity)
    {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template <typename T>
    T &GetComponent(Entity entity)
    {
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(Entity entity)
    {
        for (auto const &pair : componentArrays)
        {
            auto const &component = pair.second;
            component->EntityDestroyed(entity);
        }
    }

private:
    std::unordered_map<const char *, ComponentType> componentTypes{};
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> componentArrays{};
    ComponentType nextComponentType{};

    template <typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char *typeName = typeid(T).name();
        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};

extern ComponentManager componentManager; // Declaración externa
