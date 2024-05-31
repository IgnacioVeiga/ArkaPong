#include "MenuState.h"
#include "PlayState.h"
#include "GameConstants.h"
#include <Game.h>

MenuState::MenuState()
{
    textManager = new TextManager();
    audioManager = new AudioManager();
    audioManager->loadSound("game_start", "assets/audio/bgm/game_start.wav");
}

MenuState::~MenuState()
{
    delete textManager;
    delete audioManager;
}

void MenuState::handleInput()
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
            audioManager->playSound("game_start");
            SDL_Delay(5000);
            Game::flowManager->changeState(new PlayState());
        }
        else if (menuOptions[selectedOption].text == "2P")
        {
            audioManager->playSound("game_start");
            SDL_Delay(5000);
            Game::flowManager->changeState(new PlayState());
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

void MenuState::update()
{
    /*
        TODO: Show animations, for example, a blinking at the text of the selected game mode.
        Another thing to show could be that after a while show the text of the game story and
        then a prepared gameplay as in the original Arkanoid.
    */
}

void MenuState::render()
{
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderClear(Game::renderer);

    textManager->renderText(GAME_TITLE, SCREEN_WIDTH / 2 - 120, 30, c_white);

    // Main menu options
    for (int i = 0; i < menuOptions.size(); ++i)
    {
        textManager->renderText(menuOptions[i].text, menuOptions[i].rect.x + 20, menuOptions[i].rect.y, c_white);

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

    textManager->renderText("pre-alpha 2024", SCREEN_WIDTH / 2 - 120, SCREEN_HEIGHT - 30, c_white);
    SDL_RenderPresent(Game::renderer);
}
