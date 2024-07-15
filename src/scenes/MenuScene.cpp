#include "MenuScene.h"
#include "PlayScene.h"
#include "../Game.h"
#include "../utilities/GameConstants.h"

MenuScene::MenuScene()
{
    textManager = new TextManager();
    audioManager = new AudioManager();
    audioManager->loadSound("game_start", "assets/audio/bgm/game_start.wav");
}

MenuScene::~MenuScene()
{
    delete textManager;
    delete audioManager;
}

void MenuScene::handleInput()
{
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    if (keystate[SDL_SCANCODE_S])
    {
        selectedOption = (selectedOption + 1) % menuOptions.size();
        SDL_Delay(250);
        return;
    }

    if (keystate[SDL_SCANCODE_W])
    {
        selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
        SDL_Delay(250);
        return;
    }

    if (keystate[SDL_SCANCODE_SPACE])
    {
        // TODO: refactor
        if (menuOptions[selectedOption].text == "1P")
        {
            audioManager->playSound("game_start", true);
            Game::flowManager->changeScene(new PlayScene());
        }
        else if (menuOptions[selectedOption].text == "2P")
        {
            audioManager->playSound("game_start", true);
            Game::flowManager->changeScene(new PlayScene());
        }
        else if (menuOptions[selectedOption].text == "Settings")
        {
            return;
        }
        else
        {
            Game::game_on = false;
        }
    }
    if (keystate[SDL_SCANCODE_ESCAPE])
    {
        Game::game_on = false;
    }
}

void MenuScene::update()
{
    /*
        TODO: Show animations, for example, a blinking at the text of the selected game mode.
        Another thing to show could be that after a while show the text of the game story and
        then a prepared gameplay as in the original Arkanoid.
    */
}

void MenuScene::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    textManager->renderText(GAME_TITLE, SCREEN_WIDTH / 2, PADDLE_OFFSET, TextAlignment::CENTER, 24);

    // Main menu options
    for (int i = 0; i < menuOptions.size(); ++i)
    {
        textManager->renderText(menuOptions[i].text, menuOptions[i].rect.x + 20, menuOptions[i].rect.y);

        if (i == selectedOption)
        {
            SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 127);
        }
        else
        {
            SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
        }
        SDL_RenderFillRect(Game::renderer, &menuOptions[i].rect);
    }

    textManager->renderText("pre-alpha 2024", SCREEN_WIDTH / 2, SCREEN_HEIGHT - PADDLE_OFFSET, c_gray, TextAlignment::CENTER, 8);
    SDL_RenderPresent(Game::renderer);
}
