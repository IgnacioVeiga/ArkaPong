#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <unordered_set>
#include <SDL2/SDL.h>
#include "CoreConstants.h"
#include "Vec2.h"
#include "CollisionDetection.h"

class QuadTree : public CollisionDetection
{
public:
    QuadTree(int level = 0, SDL_FRect bounds = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT})
        : level(level), bounds(bounds)
    {
        nodes.resize(4);
    }

    void Clear() override
    {
        entities.clear();
        for (auto &node : nodes)
        {
            if (node)
            {
                node->Clear();
                node.reset();
            }
        }
    }

    void Insert(Entity entity, Vec2 position, SDL_FRect collider) override
    {
        if (nodes[0])
        {
            int index = GetIndex(collider);
            if (index != -1)
            {
                nodes[index]->Insert(entity, position, collider);
                return;
            }
        }

        entities.push_back({entity, collider});

        if (entities.size() > MAX_ENTITIES && level < MAX_LEVELS)
        {
            if (!nodes[0])
            {
                Split();
            }

            auto it = entities.begin();
            while (it != entities.end())
            {
                int index = GetIndex(it->second);
                if (index != -1)
                {
                    nodes[index]->Insert(it->first, position, it->second);
                    it = entities.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    std::vector<Entity> Retrieve(const SDL_FRect &collider) override
    {
        std::unordered_set<Entity> uniqueEntities;
        int index = GetIndex(collider);
        if (index != -1 && nodes[0])
        {
            auto childEntities = nodes[index]->Retrieve(collider);
            uniqueEntities.insert(childEntities.begin(), childEntities.end());
        }

        for (const auto &pair : entities)
        {
            uniqueEntities.insert(pair.first);
        }

        return {uniqueEntities.begin(), uniqueEntities.end()};
    }

    // void GetPotentialCollisions(std::vector<std::pair<Entity, Entity>> &collisions) override
    // {
    //     for (size_t i = 0; i < entities.size(); ++i)
    //     {
    //         for (size_t j = i + 1; j < entities.size(); ++j)
    //         {
    //             if (SDL_HasIntersectionF(&entities[i].second, &entities[j].second))
    //             {
    //                 collisions.push_back({entities[i].first, entities[j].first});
    //             }
    //         }
    //     }

    //     for (auto &node : nodes)
    //     {
    //         if (node)
    //         {
    //             node->GetPotentialCollisions(collisions);
    //         }
    //     }
    // }

private:
    void Split()
    {
        float subWidth = bounds.w / 2.0f;
        float subHeight = bounds.h / 2.0f;
        float x = bounds.x;
        float y = bounds.y;

        nodes[0] = std::make_unique<QuadTree>(level + 1, SDL_FRect{x + subWidth, y, subWidth, subHeight});
        nodes[1] = std::make_unique<QuadTree>(level + 1, SDL_FRect{x, y, subWidth, subHeight});
        nodes[2] = std::make_unique<QuadTree>(level + 1, SDL_FRect{x, y + subHeight, subWidth, subHeight});
        nodes[3] = std::make_unique<QuadTree>(level + 1, SDL_FRect{x + subWidth, y + subHeight, subWidth, subHeight});
    }

    int GetIndex(const SDL_FRect &collider)
    {
        int index = -1;
        double verticalMidpoint = bounds.x + (bounds.w / 2.0);
        double horizontalMidpoint = bounds.y + (bounds.h / 2.0);

        bool topQuadrant = (collider.y < horizontalMidpoint && collider.y + collider.h < horizontalMidpoint);
        bool bottomQuadrant = (collider.y > horizontalMidpoint);

        if (collider.x < verticalMidpoint && collider.x + collider.w < verticalMidpoint)
        {
            if (topQuadrant)
            {
                index = 1;
            }
            else if (bottomQuadrant)
            {
                index = 2;
            }
        }
        else if (collider.x > verticalMidpoint)
        {
            if (topQuadrant)
            {
                index = 0;
            }
            else if (bottomQuadrant)
            {
                index = 3;
            }
        }

        return index;
    }

    int level;
    SDL_FRect bounds;
    std::vector<std::pair<Entity, SDL_FRect>> entities;
    std::vector<std::unique_ptr<QuadTree>> nodes;
    static const int MAX_ENTITIES = 10;
    static const int MAX_LEVELS = 5;
};