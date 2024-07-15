#pragma once
#include "Scene.h"
#include <memory>

class SceneManager
{
public:
    void LoadScene(Scene *scene);
    void Update(float deltaTime);
    void Render(SDL_Renderer *renderer);

private:
    Scene *currentScene = nullptr;
};
