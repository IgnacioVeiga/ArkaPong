#pragma once

#include <unordered_map>
#include <memory>
#include <array>
#include <cassert>
#include <typeindex>
#include "Core/Entity/Entity.h"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;

    virtual void EntityDestroyed(Entity entity) = 0;

    virtual bool HasData(Entity entity) const = 0;
};

template<typename T>
class ComponentArray final : public IComponentArray {
public:
    void InsertData(const Entity entity, T component) {
        assert(
            mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() &&
            "Component added to same entity more than once.");

        // Put new entry at end and update the maps
        size_t newIndex = mSize;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray[newIndex] = component;
        ++mSize;
    }

    void RemoveData(const Entity entity) {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = mSize - 1;
        mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

        // Update map to point to moved spot
        const Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
        mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;
        mEntityToIndexMap.erase(entity);
        mIndexToEntityMap.erase(indexOfLastElement);
        --mSize;
    }

    T &GetData(Entity entity) {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

        // Return a reference to the entity's component
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void EntityDestroyed(Entity entity) override {
        if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
            // Remove the entity's component if it existed
            RemoveData(entity);
        }
    }

    bool HasData(const Entity entity) const override {
        return mEntityToIndexMap.find(entity) != mEntityToIndexMap.end();
    }

private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> mComponentArray;

    // Map from an entity ID to an array index.
    std::unordered_map<Entity, size_t> mEntityToIndexMap;

    // Map from an array index to an entity ID.
    std::unordered_map<size_t, Entity> mIndexToEntityMap;

    // Total size of valid entries in the array.
    size_t mSize = 0;
};

class ComponentManager {
public:
    template<typename T>
    void RegisterComponent() {
        const auto typeKey = std::type_index(typeid(T));

        assert(mComponentTypes.find(typeKey) == mComponentTypes.end() && "Registering component type more than once.");

        // Add this component type to the component type map
        mComponentTypes.insert({typeKey, mNextComponentType});

        // Create a ComponentArray pointer and add it to the component arrays map
        mComponentArrays.insert({typeKey, std::make_shared<ComponentArray<T> >()});

        // Increment the value so that the next component registered will be different
        ++mNextComponentType;
    }

    template<typename T>
    ComponentType GetComponentType() {
        const auto typeKey = std::type_index(typeid(T));
        assert(mComponentTypes.find(typeKey) != mComponentTypes.end() && "Component not registered before use.");
        // Return this component's type - used for creating signatures
        return mComponentTypes[typeKey];
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        // Add a component to the array for an entity
        GetComponentArray<T>()->InsertData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        // Remove a component from the array for an entity
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T &GetComponent(Entity entity) {
        // Get a reference to a component from the array for an entity
        return GetComponentArray<T>()->GetData(entity);
    }

    void EntityDestroyed(const Entity entity) {
        // Notify each component array that an entity has been destroyed
        // If it has a component for that entity, it will remove it
        for (auto const &pair: mComponentArrays) {
            auto const &component = pair.second;
            component->EntityDestroyed(entity);
        }
    }

    template<typename T>
    bool HasComponent(const Entity entity) {
        const auto typeKey = std::type_index(typeid(T));
        auto it = mComponentArrays.find(typeKey);
        if (it == mComponentArrays.end() || !it->second) {
            return false;
        }
        return it->second->HasData(entity);
    }

    const std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> &GetAllComponentArrays() const {
        return mComponentArrays;
    }
private:
    // Map from a stable type key to a component type
    std::unordered_map<std::type_index, ComponentType> mComponentTypes{};

    // Map from a stable type key to a component array
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> mComponentArrays;

    // The component type to be assigned to the next registered component - starting at 0
    ComponentType mNextComponentType{};

    // Convenience function to get the statically casted pointer to the ComponentArray of type T.
    template<typename T>
    std::shared_ptr<ComponentArray<T> > GetComponentArray() {
        const auto typeKey = std::type_index(typeid(T));
        assert(mComponentTypes.find(typeKey) != mComponentTypes.end() && "Component not registered before use.");
        return std::static_pointer_cast<ComponentArray<T> >(mComponentArrays[typeKey]);
    }
};
