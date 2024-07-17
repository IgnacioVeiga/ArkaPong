#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../scenes/Scene.h"

class SceneManager
{
private:
    Scene *currentScene;

public:
    SceneManager(Scene* newScene);
    ~SceneManager();

    void changeScene(Scene *newScene);
    void handleInput();
    void update();
    void render();
};

#endif
