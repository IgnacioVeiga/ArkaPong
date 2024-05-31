#include "Entity.h"
#include "unordered_map"

class ComponentManager
{
public:
    template <typename T>
    void addComponent(Entity::Id entity, T component)
    {
        auto &componentArray = getComponentArray<T>();
        componentArray[entity] = component;
    }

    template <typename T>
    T *getComponent(Entity::Id entity)
    {
        auto &componentArray = getComponentArray<T>();
        auto it = componentArray.find(entity);
        if (it != componentArray.end())
        {
            return &it->second;
        }
        return nullptr;
    }

private:
    template <typename T>
    std::unordered_map<Entity::Id, T> &getComponentArray()
    {
        static std::unordered_map<Entity::Id, T> componentArray;
        return componentArray;
    }
};
