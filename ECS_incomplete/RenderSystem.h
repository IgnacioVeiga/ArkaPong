#include "Components.h"
#include "Entity.h"
#include <vector>
#include <utility>
#include "../src/Game.h"

class RenderSystem
{
public:
    void render(std::vector<std::pair<PositionComponent, RenderComponent>> &entities)
    {
        for (auto &entity : entities)
        {
            SDL_Rect dest = entity.second.rect;
            dest.x = static_cast<int>(entity.first.x);
            dest.y = static_cast<int>(entity.first.y);
            SDL_RenderCopy(Game::renderer, entity.second.texture, nullptr, &dest);
        }
    }
};