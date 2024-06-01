#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "../entities/Ball.h"
#include "../managers/CollisionManager.h"
#include "../managers/TextManager.h"

class PlayState : public GameState
{
public:
	PlayState();
	~PlayState();
	void handleInput() override;
	void update() override;
	void render() override;
private:
	Paddle playerLeft;
	Paddle playerRight;
	Ball ball;
	TextManager* textManager;
	AudioManager* audioManager;
	ScoreManager* scoreManager;
	CollisionManager* collisionManager;
};

#endif
