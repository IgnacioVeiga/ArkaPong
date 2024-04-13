#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include "Ball.h"
#include "TextManager.h"
#include "AudioManager.h"

class GameState
{
public:
    GameState(SDL_Renderer *renderer);
    ~GameState();
    
    void handleInput();
    void update();
    void render(SDL_Renderer *renderer);
    int getPlayerLeftScore() const;
    int getPlayerRightScore() const;
    void increaseScoreLeft();
    void increaseScoreRight();

private:
    SDL_Renderer *renderer;
    Paddle playerLeft;
    Paddle playerRight;
    Ball ball;
    TextManager *textManager;
    AudioManager *audioManager;

    int playerLeftScore;
    int playerRightScore;

    void checkCollision();
    void resetBall();
};

#endif
