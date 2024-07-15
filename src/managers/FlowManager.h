#ifndef FLOW_MANAGER_H
#define FLOW_MANAGER_H

#include "../scenes/GameScene.h"

class FlowManager
{
private:
    GameScene *currentScene;

public:
    FlowManager(GameScene* newScene);
    ~FlowManager();

    void changeScene(GameScene *newScene);
    void handleInput();
    void update();
    void render();
};

#endif
