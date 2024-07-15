#include "GameOverScene.h"
#include "../utilities/GameConstants.h"
#include "./MenuScene.h"
#include "../Game.h"

GameOverScene::GameOverScene()
{
	countdown = 5;
	countdownTimer = SDL_GetTicks();
	textManager = new TextManager();

	audioManager = new AudioManager();
	audioManager->loadSound("game_over", "assets/audio/bgm/game_over.wav");
	audioManager->playSound("game_over", true);
}

GameOverScene::~GameOverScene()
{
	delete textManager;
	delete audioManager;
}

void GameOverScene::handleInput()
{
	// GameScene.h implementation, may be unnecessary
}

void GameOverScene::update()
{
	// Countdown to go to MenuScene
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - countdownTimer > 1000)
	{
		countdown--;
		countdownTimer = currentTime;
		if (countdown <= 0)
		{
			Game::sceneManager->changeScene(new MenuScene());
		}
	}
	return;
}

void GameOverScene::render()
{
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Game::renderer);
	textManager->renderText("Game Over", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TextAlignment::CENTER);
	SDL_RenderPresent(Game::renderer);
}
