#ifndef PAUSE_SCENE_H
#define PAUSE_SCENE_H

#include "Scene.h"
#include "../managers/TextManager.h"

class PauseScene : public Scene
{
private:
    TextManager *textManager;

public:
    PauseScene();
    ~PauseScene();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif
