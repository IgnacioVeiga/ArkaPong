#pragma once

#include <unordered_map>
#include <SDL2/SDL_rect.h>
#include "Constants.h"
#include "Enums.h"

std::unordered_map<BrickType, std::pair<int, int>> brickTypeMap = {
    {BrickType::White, {0, 0}},
    {BrickType::Salmon, {8, 0}},
    {BrickType::LightBlue, {16, 0}},
    {BrickType::Green, {24 ,0}},
    {BrickType::Red, {32, 0}},
    {BrickType::Blue, {40, 0}},
    {BrickType::Pink, {48, 0}},
    {BrickType::Orange, {56, 0}},
    {BrickType::Iron, {0, 16}},
    {BrickType::Gold, {0, 32}}};

SDL_Rect GetBrickSrcRect(BrickType brickType)
{
    SDL_Rect srcRect;

    if (brickType == BrickType::None)
    {
        // This should be unnecessary!
        srcRect = {0, 0, 0, 0};
    }
    else if (brickTypeMap.find(brickType) != brickTypeMap.end())
    {
        srcRect.x = brickTypeMap[brickType].first;
        srcRect.y = brickTypeMap[brickType].second;
        srcRect.w = BRICK_WIDTH;
        srcRect.h = BRICK_HEIGHT;
    }
    else
    {
        // A white brick as default
        srcRect = {0, 0, BRICK_WIDTH, BRICK_HEIGHT};
    }

    return srcRect;
}
