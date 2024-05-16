#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "Paddle.h"
#include "Ball.h"
#include "TextManager.h"
#include "CollisionManager.h"
#include "ScoreManager.h"
#include "FlowManager.h"

class PlayState : public GameState
{
private:
    Paddle playerLeft;
    Paddle playerRight;
    Ball ball;
    
    TextManager *textManager;
    AudioManager *audioManager;
    ScoreManager *scoreManager;
    CollisionManager *collisionManager;

public:
    PlayState();
    ~PlayState();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif
