#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../scenes/GameScene.h"

class SceneManager
{
private:
    GameScene *currentScene;

public:
    SceneManager(GameScene* newScene);
    ~SceneManager();

    void changeScene(GameScene *newScene);
    void handleInput();
    void update();
    void render();
};

#endif
