#ifndef PLAY_SCENE_H
#define PLAY_SCENE_H

#include "GameScene.h"
#include "../entities/Ball.h"
#include "../managers/CollisionManager.h"
#include "../managers/TextManager.h"

class PlayScene : public GameScene
{
public:
	PlayScene();
	~PlayScene();
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
