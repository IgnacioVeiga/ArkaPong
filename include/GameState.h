#ifndef GAMESTATE_H
#define GAMESTATE_H

class GameState
{
public:
    GameState();
    void scorePointLeft();
    void scorePointRight();
    int getPlayerLeftScore() const;
    int getPlayerRightScore() const;
    void resetScores();

private:
    int playerLeftScore;
    int playerRightScore;
};

#endif
