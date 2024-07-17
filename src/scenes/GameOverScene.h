#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include "Scene.h"
#include "../managers/TextManager.h"
#include "../managers/AudioManager.h"

class GameOverScene : public Scene
{
public:
    GameOverScene();
    ~GameOverScene();
    void handleInput() override;
    void update() override;
    void render() override;

private:
    TextManager *textManager;
    AudioManager* audioManager;

    Uint32 countdownTimer;
    int countdown;
};

#endif
