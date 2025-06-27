#pragma once

#include <SDL2/SDL_rect.h>
#include <cstddef>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "CollisionDetection.h"
#include "CoreConstants.h"
#include "../Entity/Entity.h"

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

class SpatialHash final : public CollisionDetection {
public:
    SpatialHash() {
    }

    void Insert(const Entity entity, Vec2 position, const SDL_FRect collider) override {
        const int startX = static_cast<int>(collider.x / CELL_GRID_SIZE);
        const int startY = static_cast<int>(collider.y / CELL_GRID_SIZE);
        const int endX = static_cast<int>((collider.x + collider.w) / CELL_GRID_SIZE);
        const int endY = static_cast<int>((collider.y + collider.h) / CELL_GRID_SIZE);

        for (int x = startX; x <= endX; ++x) {
            for (int y = startY; y <= endY; ++y) {
                mHashTable[std::make_pair(x, y)].push_back(entity);
            }
        }
    }

    std::vector<Entity> Retrieve(const SDL_FRect &collider) override {
        std::unordered_set<Entity> uniqueEntities;
        const int startX = static_cast<int>(collider.x / CELL_GRID_SIZE);
        const int startY = static_cast<int>(collider.y / CELL_GRID_SIZE);
        const int endX = static_cast<int>((collider.x + collider.w) / CELL_GRID_SIZE);
        const int endY = static_cast<int>((collider.y + collider.h) / CELL_GRID_SIZE);

        for (int x = startX; x <= endX; ++x) {
            for (int y = startY; y <= endY; ++y) {
                if (auto cell = mHashTable.find({x, y}); cell != mHashTable.end()) {
                    uniqueEntities.insert(cell->second.begin(), cell->second.end());
                }
            }
        }
        return {uniqueEntities.begin(), uniqueEntities.end()};
    }

    void Clear() override {
        mHashTable.clear();
    }

    // void GetPotentialCollisions(std::vector<std::pair<Entity, Entity> > &collisions) const override {
    //     for (const auto &cell: mHashTable) {
    //         const auto &entities = cell.second;
    //         for (size_t i = 0; i < entities.size(); ++i) {
    //             for (size_t j = i + 1; j < entities.size(); ++j) {
    //                 auto &colliderA = Core::coordinator.GetComponent<RigidBodyComponent>(entities[i]).collider;
    //                 auto &colliderB = Core::coordinator.GetComponent<RigidBodyComponent>(entities[j]).collider;
    //                 if (SDL_HasIntersectionF(&colliderA, &colliderB)) {
    //                     collisions.push_back({entities[i], entities[j]});
    //                 }
    //             }
    //         }
    //     }
    // }

private:
    std::unordered_map<std::pair<int, int>, std::vector<Entity>, pair_hash> mHashTable;
};
