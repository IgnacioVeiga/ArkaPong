#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include "../Entities/BrickEntity.h"
#include "../Entities/BallEntity.h"
#include "../Entities/PaddleEntity.h"
#include "../Systems/RoundSystem.h"
#include "Core/Entity/AudioEntity.h"
#include "Core/Entity/AnimatedEntity.h"
#include "Core/Entity/InputEntity.h"
#include "Core/System/BaseSystem.h"

class GameScene final : public Scene {
public:
    void Init() override {
        currentLevelIndex = 0;

        CreateTileBackgroundEntity("TileBG", ROUND_SCENE, BGS_SPRITE_FILEPATH);
        LoadCurrentLevel();
        ballEntity = CreateBallEntity("Ball", ROUND_SCENE);
        CreatePaddleEntity("PlayerLeft", ROUND_SCENE, Side::LEFT);
        CreatePaddleEntity("PlayerRight", ROUND_SCENE, Side::RIGHT);
        CreateTextEntity(
            PLAYER_LEFT_SCORE_ENTITY,
            ROUND_SCENE,
            "P1: 0",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(16, 16));

        CreateTextEntity(
            PLAYER_RIGHT_SCORE_ENTITY,
            ROUND_SCENE,
            "P2: 0",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(static_cast<float>(GetGameWidth() - 16), 16.0f),
            Side::RIGHT);

        CreateTextEntity(
            ROUND_LEVEL_ENTITY,
            ROUND_SCENE,
            "Stage 1",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_XS,
            Vec2(static_cast<float>(GetGameWidth()) / 2.0f, 16.0f),
            Side::CENTER);

        CreateTextEntity(
            ROUND_BANNER_ENTITY,
            ROUND_SCENE,
            "",
            C_GREEN,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(static_cast<float>(GetGameWidth()) / 2.0f, static_cast<float>(GetGameHeight()) / 2.0f),
            Side::CENTER);

        CreateTextEntity(
            ROUND_STATUS_ENTITY,
            ROUND_SCENE,
            "First to " + std::to_string(GetWinningScore()) + " points",
            C_GREEN,
            RETRO_FONT_FILEPATH,
            FONT_XS,
            Vec2(static_cast<float>(GetGameWidth()) / 2.0f, static_cast<float>(GetGameHeight() - 16)),
            Side::CENTER);

        CreateBGMEntity("BGM", ROUND_SCENE, ROUND_START_BGM_FILEPATH);

        CreateAnimatedEntity(
            "Enemy",
            ROUND_SCENE,
            ENEMIES_SPRITE_FILEPATH,
            8, // frame count
            16, // frame width
            16, // frame height
            100, // animation speed
            true, // loop
            Vec2((static_cast<float>(GetGameWidth()) / 2.0f) - 8.0f, 16.0f) // position
        );

        CreateInputEntity(
            "RoundInput",
            ROUND_SCENE,
            {
                InputBehavior{
                    SDL_SCANCODE_BACKSPACE,
                    SDLK_BACKSPACE,
                    [](const Entity) { Core::GetSceneManager().ChangeScene(TITLE_SCENE); }
                },
                InputBehavior{
                    SDL_SCANCODE_RETURN,
                    SDLK_RETURN,
                    [this](const Entity) {
                        if (const auto roundSystem = Core::GetCoordinator().GetSystem<RoundSystem>();
                            roundSystem && roundSystem->CanAdvanceLevel()) {
                            AdvanceToNextLevel();
                            return;
                        }

                        if (roundSystem && (roundSystem->IsMatchOver() || roundSystem->IsCampaignCompleted())) {
                            Core::GetSceneManager().ChangeScene(ROUND_SCENE);
                        }
                    }
                },
                InputBehavior{
                    SDL_SCANCODE_KP_ENTER,
                    SDLK_KP_ENTER,
                    [this](const Entity) {
                        if (const auto roundSystem = Core::GetCoordinator().GetSystem<RoundSystem>();
                            roundSystem && roundSystem->CanAdvanceLevel()) {
                            AdvanceToNextLevel();
                            return;
                        }

                        if (roundSystem && (roundSystem->IsMatchOver() || roundSystem->IsCampaignCompleted())) {
                            Core::GetSceneManager().ChangeScene(ROUND_SCENE);
                        }
                    }
                }
            },
            150);

        auto &ballRigidBody = Core::GetCoordinator().GetComponent<RigidBodyComponent>(ballEntity);
        ballRigidBody.onOutOfBounds = [](const Entity self, const BoundsSide side) {
            if (side == BoundsSide::Left || side == BoundsSide::Right) {
                if (auto roundSystem = Core::GetCoordinator().GetSystem<RoundSystem>()) {
                    const bool matchOver = roundSystem->AwardPoint(side == BoundsSide::Left ? Side::RIGHT : Side::LEFT);
                    if (matchOver) {
                        CenterBallEntity(self);
                        StopBallEntity(self);
                    } else {
                        ResetBallEntity(self);
                    }
                    return;
                }
                ResetBallEntity(self);
                return;
            }

            auto &rigidBody = Core::GetCoordinator().GetComponent<RigidBodyComponent>(self);
            rigidBody.velocity.y = -rigidBody.velocity.y;
        };

        if (auto roundSystem = Core::GetCoordinator().GetSystem<RoundSystem>()) {
            roundSystem->Reset();
            roundSystem->StartLevel(currentLevelIndex);
        }
    };

    void Update(const float delta_time) override {
        Core::GetCoordinator().GetSystem<AnimationSystem>()->Update();
        Core::GetCoordinator().GetSystem<AudioSystem>()->Update();
        Core::GetCoordinator().GetSystem<InputSystem>()->Update();
        Core::GetCoordinator().GetSystem<TileBackgroundSystem>()->Update();
        Core::GetCoordinator().GetSystem<PathSystem>()->Update(delta_time);
        Core::GetCoordinator().GetSystem<PhysicsSystem>()->Update(delta_time);
        if (auto roundSystem = Core::GetCoordinator().GetSystem<RoundSystem>();
            roundSystem && roundSystem->CheckLevelClear() && Core::GetCoordinator().EntityExists(ballEntity)) {
            CenterBallEntity(ballEntity);
            StopBallEntity(ballEntity);
        }
        Core::GetCoordinator().GetSystem<SpriteSystem>()->Update();
        Core::GetCoordinator().GetSystem<TextSystem>()->Update();
    };

    void Cleanup() override {
        ballEntity = MAX_ENTITIES;
        Core::GetCoordinator().GetSystem<BaseSystem>()->DestroyEntitiesByScene(ROUND_SCENE);
    }

private:
    Entity ballEntity = MAX_ENTITIES;
    size_t currentLevelIndex = 0;

    bool LoadCurrentLevel() {
        const auto &levelFiles = GetLevelFiles();
        if (levelFiles.empty() || currentLevelIndex >= levelFiles.size()) {
            std::cerr << "No level file available for index " << currentLevelIndex << std::endl;
            return false;
        }

        return LoadLevel(levelFiles[currentLevelIndex]);
    }

    bool AdvanceToNextLevel() {
        const auto &levelFiles = GetLevelFiles();
        const size_t nextLevelIndex = currentLevelIndex + 1;
        if (nextLevelIndex >= levelFiles.size()) {
            return false;
        }

        DestroyCurrentLevelBricks();
        currentLevelIndex = nextLevelIndex;

        if (!LoadCurrentLevel()) {
            return false;
        }

        if (Core::GetCoordinator().EntityExists(ballEntity)) {
            ResetBallEntity(ballEntity);
        }

        if (auto roundSystem = Core::GetCoordinator().GetSystem<RoundSystem>()) {
            roundSystem->StartLevel(currentLevelIndex);
        }

        return true;
    }

    void DestroyCurrentLevelBricks() {
        std::vector<Entity> bricksToDestroy;

        // Destroy only the level geometry immediately so the scene can reuse
        // the same paddles, HUD, and audio while moving to the next stage.
        for (const Entity entity : Core::GetCoordinator().GetAllEntities()) {
            if (!Core::GetCoordinator().HasComponent<BrickComponent>(entity) ||
                !Core::GetCoordinator().HasComponent<BaseComponent>(entity)) {
                continue;
            }

            const auto &baseComponent = Core::GetCoordinator().GetComponent<BaseComponent>(entity);
            if (baseComponent.scene_name == ROUND_SCENE) {
                bricksToDestroy.push_back(entity);
            }
        }

        for (const Entity entity : bricksToDestroy) {
            Core::GetCoordinator().DestroyEntity(entity);
        }
    }

    bool LoadLevel(const std::string &level_file) {
        std::ifstream infile(level_file);
        if (!infile.is_open()) {
            std::cerr << "Could not open level file: " << level_file << std::endl;
            return false;
        }

        std::string line;

        // Read the first line for rows and columns
        if (!std::getline(infile, line)) {
            std::cerr << "Level file is empty: " << level_file << std::endl;
            return false;
        }

        std::istringstream iss(line);
        int rows = 0;
        int cols = 0;
        if (!(iss >> rows >> cols) || rows <= 0 || cols <= 0) {
            std::cerr << "Invalid level header in: " << level_file << std::endl;
            return false;
        }

        std::vector<std::vector<int>> grid;
        grid.reserve(rows);

        int row = 0;
        while (std::getline(infile, line) && row < rows) {
            std::istringstream rowStream(line);
            std::vector<int> rowValues;
            rowValues.reserve(cols);

            int blockType = 0;
            while (rowStream >> blockType && static_cast<int>(rowValues.size()) < cols) {
                rowValues.push_back(blockType);
            }

            if (static_cast<int>(rowValues.size()) != cols) {
                std::cerr << "Invalid column count in level file: " << level_file << " row " << row << std::endl;
                return false;
            }

            if (rowStream >> blockType) {
                std::cerr << "Too many columns in level file: " << level_file << " row " << row << std::endl;
                return false;
            }

            grid.push_back(std::move(rowValues));
            ++row;
        }

        if (row != rows) {
            std::cerr << "Invalid row count in level file: " << level_file << std::endl;
            return false;
        }

        while (std::getline(infile, line)) {
            if (line.find_first_not_of(" \t\r") != std::string::npos) {
                std::cerr << "Too many rows in level file: " << level_file << std::endl;
                return false;
            }
        }

        const float brickWidth = static_cast<float>(GetBrickWidth());
        const float brickHeight = static_cast<float>(GetBrickHeight());
        const float startX = (static_cast<float>(GetGameWidth()) / 2.0f) - (static_cast<float>(cols) / 2.0f * brickWidth);
        const float startY = static_cast<float>(PADDLE_OFFSET);

        for (int parsedRow = 0; parsedRow < rows; ++parsedRow) {
            for (int col = 0; col < cols; ++col) {
                const int blockType = grid[parsedRow][col];
                if (blockType == 0) {
                    continue;
                }

                CreateBrickEntity(
                    "Brick R" + std::to_string(parsedRow) + " C" + std::to_string(col),
                    ROUND_SCENE,
                    Vec2(startX + static_cast<float>(col) * brickWidth,
                         startY + static_cast<float>(parsedRow) * brickHeight),
                    blockType);
            }
        }

        return true;
    }
};
