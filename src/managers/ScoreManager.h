#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

class ScoreManager
{
public:
    ScoreManager();
    void increaseScoreLeft();
    void increaseScoreRight();
    int getPlayerLeftScore() const;
    int getPlayerRightScore() const;

private:
    int playerLeftScore;
    int playerRightScore;
};

#endif
