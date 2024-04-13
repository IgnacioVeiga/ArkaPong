#include "GameState.h"

GameState::GameState() : playerLeftScore(0), playerRightScore(0) {}

void GameState::scorePointLeft()
{
    playerLeftScore++;
}

void GameState::scorePointRight()
{
    playerRightScore++;
}

int GameState::getPlayerLeftScore() const
{
    return playerLeftScore;
}

int GameState::getPlayerRightScore() const
{
    return playerRightScore;
}

void GameState::resetScores()
{
    playerLeftScore = 0;
    playerRightScore = 0;
}
