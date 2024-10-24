#pragma once

#include <unordered_map>
#include <vector>
#include <SDL2/SDL.h>
#include "ECS/Entity/Entity.h"
#include "Constants.h"
#include <unordered_set>

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
        int startX = collider.x / CELL_GRID_SIZE;
        int startY = collider.y / CELL_GRID_SIZE;
        int endX = (collider.x + collider.w) / CELL_GRID_SIZE;
        int endY = (collider.y + collider.h) / CELL_GRID_SIZE;

        for (int x = startX; x <= endX; ++x)
        {
            for (int y = startY; y <= endY; ++y)
            {
                mHashTable[std::make_pair(x, y)].push_back(entity);
            }
        }
    }

    std::vector<Entity> Retrieve(const SDL_Rect &collider)
    {
        std::unordered_set<Entity> uniqueEntities;
        int startX = collider.x / CELL_GRID_SIZE;
        int startY = collider.y / CELL_GRID_SIZE;
        int endX = (collider.x + collider.w) / CELL_GRID_SIZE;
        int endY = (collider.y + collider.h) / CELL_GRID_SIZE;

        for (int x = startX; x <= endX; ++x)
        {
            for (int y = startY; y <= endY; ++y)
            {
                auto cell = mHashTable.find({x, y});
                if (cell != mHashTable.end())
                {
                    uniqueEntities.insert(cell->second.begin(), cell->second.end());
                }
            }
        }
        return {uniqueEntities.begin(), uniqueEntities.end()};
    }

    void Clear()
    {
        mHashTable.clear();
    }

private:
    std::unordered_map<std::pair<int, int>, std::vector<Entity>, pair_hash> mHashTable;
};