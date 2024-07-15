#include "ScoreManager.h"
#include "../Game.h"
#include "../scenes/GameOverScene.h"

ScoreManager::ScoreManager()
{
	audioManager = new AudioManager();
	audioManager->loadSound("explosion", "assets/audio/sfx/vaus_explosion.wav");
}

ScoreManager::~ScoreManager()
{
	delete audioManager;
}

void ScoreManager::increaseScore(PlayerSide player)
{
	if (player == PlayerSide::PLAYER_LEFT)
	{
		playerLeftScore++;
	}
	else
	{
		playerRightScore++;
	}

	SDL_Delay(250);
	audioManager->playSound("explosion", true);

	// Temporary condition, this will then depend on the game mode and level
	if (getPlayerLeftScore() == 10 || getPlayerRightScore() == 10)
	{
		Game::flowManager->changeScene(new GameOverScene());
	}
}

int ScoreManager::getPlayerLeftScore() const
{
	return playerLeftScore;
}

int ScoreManager::getPlayerRightScore() const
{
	return playerRightScore;
}
