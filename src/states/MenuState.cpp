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
    if (keystate[SDL_SCANCODE_SPACE])
    {
        audioManager->playSound("game_start");
        SDL_Delay(5000);
        Game::flowManager->changeState(new PlayState());
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
    textManager->renderText("Press SPACE to start", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(Game::renderer);
}
