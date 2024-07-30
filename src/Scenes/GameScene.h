#pragma once

#include <SDL2/SDL.h>
#include "Scene.h"
#include "../Game.h"
#include "../ECS/Coordinator.h"
#include "../ECS/System/InputSystem.h"
#include "../ECS/System/MovementSystem.h"
#include "../ECS/System/SpriteSystem.h"
#include "../ECS/System/AudioSystem.h"
#include "../ECS/System/CollisionSystem.h"
#include "../ECS/System/TextSystem.h"
#include "../ECS/System/Background/TileBackgroundSystem.h"
#include "../ECS/Entity/BackgroundEntity.h"
#include "../ECS/Entity/BallEntity.h"
#include "../ECS/Entity/PaddleEntity.h"
#include "../ECS/Entity/TextEntity.h"
#include "../ECS/Entity/AudioEntity.h"

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
			"assets/fonts/PressStart2P-vaV7.ttf",
			16,
			16,
			16);

		sceneEntities["PR_Score"] = CreateTextEntity(
			"P2: 0",
			C_WHITE,
			"assets/fonts/PressStart2P-vaV7.ttf",
			16,
			SCREEN_WIDTH - 16,
			16,
			TextAlignment::RIGHT);

		sceneEntities["DemoText"] = CreateTextEntity(
			"Demo text",
			C_GREEN,
			"assets/fonts/PressStart2P-vaV7.ttf",
			8,
			SCREEN_WIDTH / 2,
			SCREEN_HEIGHT - 16,
			TextAlignment::CENTER);
		sceneEntities["BGM"] = CreateBGMEntity("assets/audio/bgm/round_start.wav");
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
	};
};
