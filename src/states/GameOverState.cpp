#include "GameOverState.h"
#include "../utilities/GameConstants.h"
#include "./MenuState.h"
#include "../Game.h"

GameOverState::GameOverState()
{
	countdown = 5;
	countdownTimer = SDL_GetTicks();
	textManager = new TextManager();

	audioManager = new AudioManager();
	audioManager->loadSound("game_over", "assets/audio/bgm/game_over.wav");
	audioManager->playSound("game_over");
}

GameOverState::~GameOverState()
{
	delete textManager;
	delete audioManager;
}

void GameOverState::handleInput()
{
	// GameState.h implementation, may be unnecessary
}

void GameOverState::update()
{
	// Countdown to go to MenuState
	Uint32 currentTime = SDL_GetTicks();
	if (currentTime - countdownTimer > 1000)
	{
		countdown--;
		countdownTimer = currentTime;
		if (countdown <= 0)
		{
			Game::flowManager->changeState(new MenuState());
		}
	}
	return;
}

void GameOverState::render()
{
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderClear(Game::renderer);
	textManager->renderText("Game Over", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
	SDL_RenderPresent(Game::renderer);
}
