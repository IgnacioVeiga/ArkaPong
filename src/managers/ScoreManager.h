#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include "AudioManager.h"
#include "../entities/Paddle.h"

class ScoreManager
{
public:
    ScoreManager();
    ~ScoreManager();

    void increaseScore(PlayerSide);
    int getPlayerLeftScore() const;
    int getPlayerRightScore() const;

private:
    int playerLeftScore = 0;
    int playerRightScore = 0;

    AudioManager* audioManager;
};

#endif
