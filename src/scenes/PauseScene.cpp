#include "PauseScene.h"
#include "../utilities/GameConstants.h"
#include "../Game.h"

PauseScene::PauseScene()
{
    textManager = new TextManager();
}

PauseScene::~PauseScene()
{
    delete textManager;
}

void PauseScene::handleInput()
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_SPACE])
    {
        // Game::sceneManager->changeScene(new PlayScene());
    }
    else if (keystate[SDL_SCANCODE_ESCAPE])
    {
        Game::game_on = false;
    }
}

void PauseScene::update()
{
    // GameScene.h implementation, may be unnecessary
}

void PauseScene::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);
    textManager->renderText("Game Paused", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, TextAlignment::CENTER);
    textManager->renderText("Press SPACE to continue", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 30, TextAlignment::CENTER);
    textManager->renderText("ESC to quit", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 60, TextAlignment::CENTER);
    SDL_RenderPresent(Game::renderer);
}
