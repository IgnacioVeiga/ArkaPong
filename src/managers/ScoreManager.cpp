#include "ScoreManager.h"
#include "../Game.h"
#include "../states/GameOverState.h"

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
		Game::flowManager->changeState(new GameOverState());
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
