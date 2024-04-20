#include "MenuState.h"
#include "PlayState.h"
#include "GameConstants.h"

MenuState::MenuState(SDL_Renderer *renderer, GameFlowManager *flowMgr)
    : renderer(renderer), flowManager(flowMgr)
{
    textManager = new TextManager(renderer);
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
        // Cambiar al PlayState
        audioManager->playSound("game_start");
        SDL_Delay(5000);
        flowManager->changeState(new PlayState(renderer, flowManager));
    }
    else if (keystate[SDL_SCANCODE_ESCAPE])
    {
        // TODO: salir del juego
    }
    else if (keystate[SDL_SCANCODE_C])
    {
        // TODO: permitir cambiar a un "ConfigState"
    }
}

void MenuState::update()
{
    // Actualizar lógica del menú, como animaciones o efectos
}

void MenuState::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
    SDL_RenderClear(renderer);
    textManager->renderText("Press SPACE to start", SCREEN_WIDTH / 2 - 100, SCREEN_HEIGHT / 2);
    SDL_RenderPresent(renderer);
}
