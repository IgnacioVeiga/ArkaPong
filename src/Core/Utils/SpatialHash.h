#pragma once

#include <SDL2/SDL_rect.h>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "CoreConstants.h"
#include "../Entity/Entity.h"

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

    void Insert(Entity entity, SDL_FRect &collider)
    {
        int startX = static_cast<int>(collider.x / CELL_GRID_SIZE);
        int startY = static_cast<int>(collider.y / CELL_GRID_SIZE);
        int endX = static_cast<int>((collider.x + collider.w) / CELL_GRID_SIZE);
        int endY = static_cast<int>((collider.y + collider.h) / CELL_GRID_SIZE);

        for (int x = startX; x <= endX; ++x)
        {
            for (int y = startY; y <= endY; ++y)
            {
                mHashTable[std::make_pair(x, y)].push_back(entity);
            }
        }
    }

    std::vector<Entity> Retrieve(const SDL_FRect &collider)
    {
        std::unordered_set<Entity> uniqueEntities;
        int startX = static_cast<int>(collider.x / CELL_GRID_SIZE);
        int startY = static_cast<int>(collider.y / CELL_GRID_SIZE);
        int endX = static_cast<int>((collider.x + collider.w) / CELL_GRID_SIZE);
        int endY = static_cast<int>((collider.y + collider.h) / CELL_GRID_SIZE);

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