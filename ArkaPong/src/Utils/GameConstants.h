#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include "Core/Core.h"

constexpr auto DEFAULT_GAME_TITLE = "ArkaPong";

constexpr auto DEFAULT_BALL_SPEED = 128.0f;
constexpr auto DEFAULT_BALL_WIDTH = 5;
constexpr auto DEFAULT_BALL_HEIGHT = 5;

constexpr auto DEFAULT_PADDLE_SPEED = 8.0f;
constexpr auto PADDLE_OFFSET = 32;
constexpr auto DEFAULT_PADDLE_WIDTH = 8;
constexpr auto DEFAULT_PADDLE_HEIGHT = 32;

constexpr auto DEFAULT_BRICK_WIDTH = 8;
constexpr auto DEFAULT_BRICK_HEIGHT = 16;
constexpr auto DEFAULT_WINNING_SCORE = 5;

constexpr auto DOH_OP_BGM_FILEPATH = "assets/audio/bgm/doh_round.wav";
constexpr auto ENDING_BGM_FILEPATH = "assets/audio/bgm/ending.wav";
constexpr auto GAME_OVER_BGM_FILEPATH = "assets/audio/bgm/game_over.wav";
constexpr auto GAME_START_BGM_FILEPATH = "assets/audio/bgm/game_start.wav";
constexpr auto ROUND_START_BGM_FILEPATH = "assets/audio/bgm/round_start.wav";

constexpr auto HIT_DOH_SFX_FILEPATH = "assets/audio/sfx/ball_hit_doh.wav";
constexpr auto HIT_ENEMY_SFX_FILEPATH = "assets/audio/sfx/ball_hit_enemy.wav";
constexpr auto HIT_OBS_SFX_FILEPATH = "assets/audio/sfx/ball_hit_obstacle.wav";
constexpr auto HIT_SHIELD_SFX_FILEPATH = "assets/audio/sfx/ball_hit_shield.wav";
constexpr auto HIT_VAUS_SFX_FILEPATH = "assets/audio/sfx/ball_hit_vaus.wav";
constexpr auto DOH_END_SFX_FILEPATH = "assets/audio/sfx/doh_disappears.wav";
constexpr auto ESCAPE_SFX_FILEPATH = "assets/audio/sfx/vaus_escape.wav";
constexpr auto EXPLOSION_SFX_FILEPATH = "assets/audio/sfx/vaus_explosion.wav";
constexpr auto HOLD_SFX_FILEPATH = "assets/audio/sfx/vaus_holds_ball.wav";
constexpr auto LIFE_UP_SFX_FILEPATH = "assets/audio/sfx/vaus_life_up.wav";
constexpr auto LONG_SFX_FILEPATH = "assets/audio/sfx/vaus_longer.wav";
constexpr auto SHOT_SFX_FILEPATH = "assets/audio/sfx/vaus_shot.wav";

constexpr auto RETRO_FONT_FILEPATH = "assets/fonts/PressStart2P-vaV7.ttf";

constexpr auto BGS_SPRITE_FILEPATH = "assets/sprites/backgrounds.bmp";
constexpr auto BRICKS_SPRITE_FILEPATH = "assets/sprites/bricks.bmp";
constexpr auto DOH_SPRITE_FILEPATH = "assets/sprites/doh.bmp";
constexpr auto ENDING_SPRITE_FILEPATH = "assets/sprites/ending.bmp";
constexpr auto ENEMIES_SPRITE_FILEPATH = "assets/sprites/enemies.bmp";
constexpr auto POWER_UPS_SPRITE_FILEPATH = "assets/sprites/powerups.bmp";
constexpr auto VAUS_SPRITE_FILEPATH = "assets/sprites/vaus.bmp";
constexpr auto WALLS_SPRITE_FILEPATH = "assets/sprites/walls.bmp";

constexpr auto LEVEL_1 = "assets/levels/1.txt";
constexpr auto LEVEL_2 = "assets/levels/2.txt";

constexpr auto TITLE_SCENE = "Title";
constexpr auto ROUND_SCENE = "Round";
constexpr auto PLAYER_LEFT_SCORE_ENTITY = "PlayerLeftScore";
constexpr auto PLAYER_RIGHT_SCORE_ENTITY = "PlayerRightScore";
constexpr auto ROUND_LEVEL_ENTITY = "RoundLevel";
constexpr auto ROUND_STATUS_ENTITY = "RoundStatus";
constexpr auto ROUND_BANNER_ENTITY = "RoundBanner";

inline const json *GetProjectConfig()
{
    if (!Core::config.is_object()) {
        return nullptr;
    }

    const auto projectIt = Core::config.find("project");
    if (projectIt == Core::config.end() || !projectIt->is_object()) {
        return nullptr;
    }

    return &(*projectIt);
}

inline const json *GetProjectSection(const char *sectionName)
{
    const json *projectConfig = GetProjectConfig();
    if (!projectConfig) {
        return nullptr;
    }

    const auto sectionIt = projectConfig->find(sectionName);
    if (sectionIt == projectConfig->end() || !sectionIt->is_object()) {
        return nullptr;
    }

    return &(*sectionIt);
}

inline const json *GetEntityConfig(const char *entityName)
{
    // Read gameplay tuning from the merged runtime config so the example game
    // does not become a second source of truth for entity dimensions and speed.
    const json *entitiesConfig = GetProjectSection("entities");
    if (!entitiesConfig) {
        return nullptr;
    }

    const auto entityIt = entitiesConfig->find(entityName);
    if (entityIt == entitiesConfig->end() || !entityIt->is_object()) {
        return nullptr;
    }

    return &(*entityIt);
}

inline int GetProjectInt(const char *sectionName, const char *key, const int fallback)
{
    const json *sectionConfig = GetProjectSection(sectionName);
    if (!sectionConfig) {
        return fallback;
    }
    return sectionConfig->value(key, fallback);
}

inline int GetEntityInt(const char *entityName, const char *key, const int fallback)
{
    const json *entityConfig = GetEntityConfig(entityName);
    if (!entityConfig) {
        return fallback;
    }
    return entityConfig->value(key, fallback);
}

inline float GetEntityFloat(const char *entityName, const char *key, const float fallback)
{
    const json *entityConfig = GetEntityConfig(entityName);
    if (!entityConfig) {
        return fallback;
    }
    return entityConfig->value(key, fallback);
}

inline int GetGameWidth()
{
    return Core::GetWindow().GetLogicalWidth();
}

inline int GetGameHeight()
{
    return Core::GetWindow().GetLogicalHeight();
}

inline int GetBallWidth()
{
    return GetEntityInt("ball", "width", DEFAULT_BALL_WIDTH);
}

inline int GetBallHeight()
{
    return GetEntityInt("ball", "height", DEFAULT_BALL_HEIGHT);
}

inline float GetBallSpeed()
{
    return GetEntityFloat("ball", "speed", DEFAULT_BALL_SPEED);
}

inline int GetPaddleWidth()
{
    return GetEntityInt("paddle", "width", DEFAULT_PADDLE_WIDTH);
}

inline int GetPaddleHeight()
{
    return GetEntityInt("paddle", "height", DEFAULT_PADDLE_HEIGHT);
}

inline float GetPaddleSpeed()
{
    return GetEntityFloat("paddle", "speed", DEFAULT_PADDLE_SPEED);
}

inline int GetBrickWidth()
{
    return GetEntityInt("brick", "width", DEFAULT_BRICK_WIDTH);
}

inline int GetBrickHeight()
{
    return GetEntityInt("brick", "height", DEFAULT_BRICK_HEIGHT);
}

inline int GetWinningScore()
{
    return std::max(1, GetProjectInt("match", "winning_score", DEFAULT_WINNING_SCORE));
}

inline const std::vector<std::string> &GetLevelFiles()
{
    static const std::vector<std::string> levelFiles = {
        LEVEL_1,
        LEVEL_2
    };
    return levelFiles;
}
