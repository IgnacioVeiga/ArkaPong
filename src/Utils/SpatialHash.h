#pragma once

#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include "ECS/Entity/Entity.h"
#include "GameConstants.h"

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class SpatialHash
{
public:
    SpatialHash() {}

    void Insert(Entity entity, SDL_Rect &collider)
    {
        int cellX = collider.x / CELL_GRID_SIZE;
        int cellY = collider.y / CELL_GRID_SIZE;
        mHashTable[std::make_pair(cellX, cellY)].push_back(entity);
    }

    std::vector<Entity> Retrieve(SDL_Rect &collider)
    {
        int cellX = collider.x / CELL_GRID_SIZE;
        int cellY = collider.y / CELL_GRID_SIZE;
        return mHashTable[std::make_pair(cellX, cellY)];
    }

    void Clear()
    {
        mHashTable.clear();
    }

private:
    std::unordered_map<std::pair<int, int>, std::vector<Entity>, pair_hash> mHashTable;
};
