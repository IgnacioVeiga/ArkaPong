#pragma once

#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include "Scene.h"
#include "../Game.h"
#include "../ECS/Coordinator.h"
#include "../ECS/Entity/BackgroundEntity.h"
#include "../ECS/Entity/BallEntity.h"
#include "../ECS/Entity/PaddleEntity.h"
#include "../ECS/Entity/TextEntity.h"
#include "../ECS/Entity/AudioEntity.h"
#include "../ECS/Entity/AnimatedEntity.h"
#include "../ECS/Entity/BrickEntity.h"
#include "../ECS/System/BaseSystem.h"

class GameScene : public Scene
{
public:
	void Init() override
	{
		CreateTileBackgroundEntity("TileBG", "Game");

		std::ifstream infile("assets/levels/1.txt");
		std::string line;

		// Read the first line for rows and columns
		std::getline(infile, line);
		std::istringstream iss(line);
		int rows, cols;
		iss >> rows >> cols;

		float startX = (SCREEN_WIDTH / 2) - (cols / 2 * BRICK_WIDTH);
		float startY = PADDLE_OFFSET;
		int row = 0;

		while (std::getline(infile, line) && row < rows)
		{

			std::istringstream iss(line);
			int col = 0;
			int blockType = 0;
			while (iss >> blockType && col < cols)
			{
				// 0 = None
				if (blockType != 0)
				{
					CreateBrickEntity(
						"BrickR" + std::to_string(row) + "C" + std::to_string(col),
						"Game",
						startX + col * BRICK_WIDTH,	 // X
						startY + row * BRICK_HEIGHT, // Y
						blockType);
				}
				++col;
			}
			++row;
		}

		CreateBallEntity("Ball", "Game");
		CreatePaddleEntity("PlayerLeft", "Game", Side::LEFT);
		CreatePaddleEntity("PlayerRight", "Game", Side::RIGHT);
		CreateTextEntity(
			"PlayerLeftScore",
			"Game",
			"P1: 0",
			C_WHITE,
			RETRO_FONT_FILEPATH,
			16,
			16,
			16);

		CreateTextEntity(
			"PlayerRightScore",
			"Game",
			"P2: 0",
			C_WHITE,
			RETRO_FONT_FILEPATH,
			16,
			SCREEN_WIDTH - 16,
			16,
			Side::RIGHT);

		CreateTextEntity(
			"DemoText",
			"Game",
			"Demo text",
			C_GREEN,
			RETRO_FONT_FILEPATH,
			8,
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT - 16,
			Side::CENTER);
		CreateBGMEntity("BGM", "Game", ROUND_START_BGM_FILEPATH);
		CreateAnimatedEntity(
			"Enemy",
			"Game",
			ENEMIES_SPRITE_FILEPATH,
			8,
			16,
			16,
			100,
			true,
			(SCREEN_WIDTH / 2) - 8,
			16);
	};

	void Update(float deltaTime) override
	{
		Game::coordinator.GetSystem<BaseSystem>()->Update(deltaTime);

		// TODO: use the input system
		const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
		if (keyStates[SDL_SCANCODE_BACKSPACE])
		{
			Game::sceneManager->ChangeScene("MainMenu");
		}
	};

	void Cleanup() override
	{
		Game::coordinator.GetSystem<BaseSystem>()->DestroyEntitiesByScene("Game");
	}
};
