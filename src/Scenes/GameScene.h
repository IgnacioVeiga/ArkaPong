#pragma once

#include <SDL2/SDL.h>
#include "Scene.h"
#include "../Game.h"
#include "../ECS/Coordinator.h"
#include "../ECS/System/InputSystem.h"
#include "../ECS/System/MovementSystem.h"
#include "../ECS/System/RenderSystem.h"
#include "../ECS/System/AudioSystem.h"
#include "../ECS/System/CollisionSystem.h"
#include "../ECS/System/TextSystem.h"
#include "../ECS/System/Background/TileBackgroundSystem.h"
#include "../ECS/Entity/BackgroundEntity.h"
#include "../Utils/TextureManager.h"

class GameScene : public Scene
{
public:
	void Init() override
	{
		SDL_Texture* texture = TextureManager::LoadTexture("assets/sprites/vaus.bmp");
		SDL_Rect srcRectPaddle = {
			0,			  // X
			0,			  // Y
			PADDLE_WIDTH, // W
			PADDLE_HEIGHT // H
		};

		SDL_Texture* tileTexture = TextureManager::LoadTexture("assets/sprites/backgrounds.bmp");
		int tileTextureWidth = 160; // Mosaic texture width
		int tileTextureHeight = 32; // Mosaic texture height
		int tileWidth = 32;
		int tileHeight = 32;
		int mapWidth = 5;  // Mosaic background map width
		int mapHeight = 5; // Height of the background map in mosaics
		std::vector<int> tiles(SCREEN_HEIGHT * SCREEN_WIDTH, 0);
		sceneEntities["TileBackground"] = CreateTileBackgroundEntity(tileTexture, tileTextureWidth, tileTextureHeight, tileWidth, tileHeight, mapWidth, mapHeight, tiles);

#pragma region Ball
		sceneEntities["Ball"] = Game::coordinator.CreateEntity();
		Game::coordinator.AddComponent(
			sceneEntities["Ball"],
			PositionComponent{
				SCREEN_WIDTH / 2, // X
				SCREEN_HEIGHT / 2 // Y
			});
		Game::coordinator.AddComponent(
			sceneEntities["Ball"],
			VelocityComponent{
				BALL_SPEED, // X
				BALL_SPEED	// Y
			});
		Game::coordinator.AddComponent(
			sceneEntities["Ball"],
			RenderComponent{
				texture, // Texture
				{
				// Source rectangle
				42,		   // X
				5,		   // Y
				BALL_SIZE, // W
				BALL_SIZE  // H
			},
			{
				// Destination rectangle
				SCREEN_WIDTH / 2 - BALL_SIZE / 2,  // X
				SCREEN_HEIGHT / 2 - BALL_SIZE / 2, // Y
				BALL_SIZE,						   // W
				BALL_SIZE						   // H
			},
			SDL_FLIP_NONE // Flip
			});
		Game::coordinator.AddComponent(
			sceneEntities["Ball"],
			CollisionComponent{
				{
					// Collider rectangle
					0,		   // X
					0,		   // Y
					BALL_SIZE, // W
					BALL_SIZE  // H
				} });
#pragma endregion

#pragma region PlayerLeft
		sceneEntities["PlayerLeft"] = Game::coordinator.CreateEntity();
		Game::coordinator.AddComponent(
			sceneEntities["PlayerLeft"],
			PositionComponent{
				PADDLE_OFFSET,	  // X
				SCREEN_HEIGHT / 2 // Y
			});
		Game::coordinator.AddComponent(
			sceneEntities["PlayerLeft"],
			VelocityComponent{
				0,			 // X
				PADDLE_SPEED // Y
			});
		Game::coordinator.AddComponent(
			sceneEntities["PlayerLeft"],
			RenderComponent{
				texture,	   // Texture
				srcRectPaddle, // Source rectangle
				{
				// Destination rectangle
				PADDLE_OFFSET,						   // X
				SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, // Y
				PADDLE_WIDTH,						   // W
				PADDLE_HEIGHT						   // H
			},
			SDL_FLIP_NONE // Flip
			});
		Game::coordinator.AddComponent(
			sceneEntities["PlayerLeft"],
			CollisionComponent{
				{
					// Collider rectangle
					0,			  // X
					0,			  // Y
					PADDLE_WIDTH, // W
					PADDLE_HEIGHT // H
				} });
		Game::coordinator.AddComponent(
			sceneEntities["PlayerLeft"],
			InputComponent{
				{{"up", SDL_SCANCODE_W}, {"down", SDL_SCANCODE_S}}, // Key mappings
				{{SDL_SCANCODE_W, false}, {SDL_SCANCODE_S, false}}	// Key states
			});
#pragma endregion

#pragma region PlayerRight
		sceneEntities["PlayerRight"] = Game::coordinator.CreateEntity();
		Game::coordinator.AddComponent(
			sceneEntities["PlayerRight"],
			PositionComponent{
				SCREEN_WIDTH - PADDLE_OFFSET, // X
				SCREEN_HEIGHT / 2			  // Y
			});
		Game::coordinator.AddComponent(
			sceneEntities["PlayerRight"],
			VelocityComponent{
				0,			 // X
				PADDLE_SPEED // Y
			});
		Game::coordinator.AddComponent(
			sceneEntities["PlayerRight"],
			RenderComponent{
				texture,	   // Texture
				srcRectPaddle, // Source rectangle
				{
				// Destination rectangle
				SCREEN_WIDTH - PADDLE_OFFSET,		   // X
				SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2, // Y
				PADDLE_WIDTH,						   // W
				PADDLE_HEIGHT						   // H
			},
			SDL_FLIP_HORIZONTAL // Flip
			});
		Game::coordinator.AddComponent(
			sceneEntities["PlayerRight"],
			CollisionComponent{
				{
					// Collider rectangle
					0,			  // X
					0,			  // Y
					PADDLE_WIDTH, // W
					PADDLE_HEIGHT // H
				} });
		Game::coordinator.AddComponent(
			sceneEntities["PlayerRight"],
			InputComponent{
				{{"up", SDL_SCANCODE_UP}, {"down", SDL_SCANCODE_DOWN}}, // Key mappings
				{{SDL_SCANCODE_UP, false}, {SDL_SCANCODE_DOWN, false}}	// Key states
			});
#pragma endregion
	};

	void Update(float deltaTime) override
	{
		Game::coordinator.GetSystem<InputSystem>()->Update();
		Game::coordinator.GetSystem<MovementSystem>()->Update(deltaTime);
		Game::coordinator.GetSystem<TileBackgroundSystem>()->Update();
		Game::coordinator.GetSystem<RenderSystem>()->Update();
		Game::coordinator.GetSystem<AudioSystem>()->Update();
		Game::coordinator.GetSystem<TextSystem>()->Update();
		Game::coordinator.GetSystem<CollisionSystem>()->Update(deltaTime);
	};
};
