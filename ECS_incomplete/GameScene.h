#pragma once
#include "Scene.h"

class GameScene : public Scene
{
public:
    void Load() override;
    void Update(float deltaTime) override;
    void Render(SDL_Renderer *renderer) override;
};
