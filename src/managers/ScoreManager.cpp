#include "ScoreManager.h"

ScoreManager::ScoreManager() : playerLeftScore(0), playerRightScore(0) {}

void ScoreManager::increaseScoreLeft()
{
    playerLeftScore++;
}

void ScoreManager::increaseScoreRight()
{
    playerRightScore++;
}

int ScoreManager::getPlayerLeftScore() const
{
    return playerLeftScore;
}

int ScoreManager::getPlayerRightScore() const
{
    return playerRightScore;
}
