#pragma once

#include <SDL2/SDL.h>
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
#include "../ECS/System/InputSystem.h"
#include "../ECS/System/MovementSystem.h"
#include "../ECS/System/SpriteSystem.h"
#include "../ECS/System/AnimationSystem.h"
#include "../ECS/System/AudioSystem.h"
#include "../ECS/System/CollisionSystem.h"
#include "../ECS/System/TextSystem.h"
#include "../ECS/System/PathSystem.h"
#include "../ECS/System/Background/TileBackgroundSystem.h"

class GameScene : public Scene
{
public:
	void Init() override
	{
		sceneEntities["TileBackground"] = CreateTileBackgroundEntity();
		sceneEntities["Ball"] = CreateBallEntity();
		sceneEntities["PlayerLeft"] = CreatePaddleEntity(PlayerSide::PLAYER_LEFT);
		sceneEntities["PlayerRight"] = CreatePaddleEntity(PlayerSide::PLAYER_RIGHT);
		sceneEntities["PL_Score"] = CreateTextEntity(
			"P1: 0",
			C_WHITE,
			RETRO_FONT_FILEPATH,
			16,
			16,
			16);

		sceneEntities["PR_Score"] = CreateTextEntity(
			"P2: 0",
			C_WHITE,
			RETRO_FONT_FILEPATH,
			16,
			SCREEN_WIDTH - 16,
			16,
			TextAlignment::RIGHT);

		sceneEntities["DemoText"] = CreateTextEntity(
			"Demo text",
			C_GREEN,
			RETRO_FONT_FILEPATH,
			8,
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT - 16,
			TextAlignment::CENTER);
		sceneEntities["BGM"] = CreateBGMEntity(ROUND_START_BGM_FILEPATH);
		sceneEntities["Enemy"] = CreateAnimatedEntity(
			ENEMIES_SPRITE_FILEPATH,
			8,
			16,
			16,
			100,
			true,
			(SCREEN_WIDTH / 2) - 8,
			16);
		sceneEntities["BrickRed"] = CreateBrickEntity(
			SCREEN_WIDTH / 2 - BRICK_WIDTH,	  // X
			SCREEN_HEIGHT / 2 - BRICK_HEIGHT, // Y
			0,								  // 0 = Normal, 9 = Iron, 18 = Gold
			64								  // 0 = White, 64 = Red
		);
		sceneEntities["BrickIron"] = CreateBrickEntity(
			SCREEN_WIDTH / 2 + BRICK_WIDTH,	  // X
			SCREEN_HEIGHT / 2 + BRICK_HEIGHT, // Y
			0,								  // 0 = Normal, 9 = Iron, 18 = Gold
			32								  // 0 = White, ..., 64 = Red, ...
		);
	};

	void Update(float deltaTime) override
	{
		Game::coordinator.GetSystem<InputSystem>()->Update();
		Game::coordinator.GetSystem<MovementSystem>()->Update(deltaTime);
		Game::coordinator.GetSystem<TileBackgroundSystem>()->Update();
		Game::coordinator.GetSystem<SpriteSystem>()->Update();
		Game::coordinator.GetSystem<AudioSystem>()->Update();
		Game::coordinator.GetSystem<TextSystem>()->Update();
		Game::coordinator.GetSystem<CollisionSystem>()->Update(deltaTime);
		Game::coordinator.GetSystem<AnimationSystem>()->Update();
		Game::coordinator.GetSystem<PathSystem>()->Update();
		
		// TODO: use the input system
		const Uint8 *keyStates = SDL_GetKeyboardState(NULL);
		if (keyStates[SDL_SCANCODE_BACKSPACE])
		{
			Game::sceneManager->ChangeScene("MainMenu");
		}
	};

	void Cleanup() override
	{
		// Clean up entities and other resources
		for (const auto &entityPair : sceneEntities)
		{
			Game::coordinator.DestroyEntity(entityPair.second);
		}
		sceneEntities.clear();
	}

	void Pause() override
	{
		// Pause logic
	}

	void Resume() override
	{
		// Resume logic
	}

	bool SaveState(const std::string &filepath) override
	{
		// Serialize the scene state to a file
		return true;
	}

	bool LoadState(const std::string &filepath) override
	{
		// Deserialize the scene state from a file
		return true;
	}
};
