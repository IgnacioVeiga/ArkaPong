#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "TextManager.h"
#include "CollisionManager.h"
#include "ScoreManager.h"
#include "GameFlowManager.h"

class PlayState : public GameState
{
private:
    SDL_Renderer *renderer;
    Paddle playerLeft;
    Paddle playerRight;
    Ball ball;
    TextManager *textManager;
    AudioManager *audioManager;
    ScoreManager *scoreManager;
    CollisionManager *collisionManager;
    int countdown;
    Uint32 countdownTimer;
    bool isCountingDown;

public:
    PlayState(SDL_Renderer *renderer, GameFlowManager *flowMgr);
    ~PlayState();

    void handleInput() override;
    void update() override;
    void render(SDL_Renderer *renderer) override;
};

#endif
