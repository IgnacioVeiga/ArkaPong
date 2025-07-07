#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include "../Entities/BrickEntity.h"
#include "../Entities/BallEntity.h"
#include "../Entities/PaddleEntity.h"
#include "Core/Entity/AudioEntity.h"
#include "Core/Entity/AnimatedEntity.h"

class GameScene final : public Scene {
public:
    void Init() override {
        CreateTileBackgroundEntity("TileBG", ROUND_SCENE, BGS_SPRITE_FILEPATH);
        LoadLevel(LEVEL_1);
        CreateBallEntity("Ball", ROUND_SCENE);
        CreatePaddleEntity("PlayerLeft", ROUND_SCENE, Side::LEFT);
        CreatePaddleEntity("PlayerRight", ROUND_SCENE, Side::RIGHT);
        CreateTextEntity(
            "PlayerLeftScore",
            ROUND_SCENE,
            "P1: 0",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(16, 16));

        CreateTextEntity(
            "PlayerRightScore",
            ROUND_SCENE,
            "P2: 0",
            C_WHITE,
            RETRO_FONT_FILEPATH,
            FONT_M,
            Vec2(SCREEN_WIDTH - 16, 16),
            Side::RIGHT);

        CreateTextEntity(
            "DemoText",
            ROUND_SCENE,
            "Demo text",
            C_GREEN,
            RETRO_FONT_FILEPATH,
            FONT_XS,
            Vec2(static_cast<float_t>(SCREEN_WIDTH) / 2, SCREEN_HEIGHT - 16),
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
            Vec2((static_cast<float_t>(SCREEN_WIDTH) / 2) - 8, 16) // position
        );
    };

    void Update(const float delta_time) override {
        Core::coordinator.GetSystem<AnimationSystem>()->Update();
        Core::coordinator.GetSystem<AudioSystem>()->Update();
        Core::coordinator.GetSystem<InputSystem>()->Update();
        Core::coordinator.GetSystem<TileBackgroundSystem>()->Update();
        Core::coordinator.GetSystem<PathSystem>()->Update(delta_time);
        Core::coordinator.GetSystem<PhysicsSystem>()->Update(delta_time);
        Core::coordinator.GetSystem<SpriteSystem>()->Update();
        Core::coordinator.GetSystem<TextSystem>()->Update();

        // TODO: use the input system
        if (const Uint8 *keyStates = SDL_GetKeyboardState(nullptr); keyStates[SDL_SCANCODE_BACKSPACE]) {
            Core::scene_manager.ChangeScene(TITLE_SCENE);
        }
    };

    void Cleanup() override {
        Core::coordinator.GetSystem<BaseSystem>()->DestroyEntitiesByScene(ROUND_SCENE);
    }

private:
    void LoadLevel(std::string level_file) {
        std::ifstream infile(level_file);
        std::string line;

        // Read the first line for rows and columns
        std::getline(infile, line);
        std::istringstream iss(line);
        int rows, cols;
        iss >> rows >> cols;

        float startX = (SCREEN_WIDTH / 2.0f) - (static_cast<float_t>(cols) / 2.0f * BRICK_WIDTH);
        float startY = PADDLE_OFFSET;
        int row = 0;

        while (std::getline(infile, line) && row < rows) {
            std::istringstream iss(line);
            int col = 0;
            int blockType = 0;

            while (iss >> blockType && col < cols) {
                // 0 = None
                if (blockType != 0) {
                    CreateBrickEntity(
                        "Brick R" + std::to_string(row) + " C" + std::to_string(col),
                        ROUND_SCENE,
                        Vec2(startX + static_cast<float_t>(col) * BRICK_WIDTH,
                             startY + static_cast<float_t>(row) * BRICK_HEIGHT),
                        blockType);
                }
                ++col;
            }
            ++row;
        }
    }
};
