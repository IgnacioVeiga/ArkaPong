#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include "System.h"

class SystemManager
{
public:
    template <typename T>
    void RegisterSystem()
    {
        auto system = std::make_shared<T>();
        systems[typeid(T)] = system;
    }

    template <typename T>
    std::shared_ptr<T> GetSystem()
    {
        return std::static_pointer_cast<T>(systems[typeid(T)]);
    }

    template <typename T, typename ComponentType>
    void AddComponentType()
    {
        componentTypes[typeid(T)].push_back(typeid(ComponentType));
    }

    void UpdateSystems(float deltaTime)
    {
        for (auto &[type, system] : systems)
        {
            system->Update(deltaTime);
        }
    }

    void RenderSystems(SDL_Renderer *renderer)
    {
        for (auto &[type, system] : systems)
        {
            system->Render(renderer);
        }
    }

private:
    std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
    std::unordered_map<std::type_index, std::vector<std::type_index>> componentTypes;
};
