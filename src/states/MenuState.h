#ifndef MENU_STATE_H
#define MENU_STATE_H

#include "vector"
#include "GameState.h"
#include <string>
#include "../managers/TextManager.h"
#include "../managers/AudioManager.h"

struct MenuOption
{
    std::string text;
    SDL_Rect rect;
};

class MenuState : public GameState
{
private:
    TextManager *textManager;
    AudioManager *audioManager;

    SDL_Color c_white = {255, 255, 255, 255};
    SDL_Color c_gray = {255, 255, 255, 127};

    // Opciones del menú
    std::vector<MenuOption> menuOptions = {
        {"1P", {350, 200, 16, 16}},
        {"2P", {350, 250, 16, 16}},
        {"Settings", {350, 300, 16, 16}},
        {"Exit", {350, 350, 16, 16}}};

    int selectedOption = 0;

public:
    MenuState();
    ~MenuState();

    void handleInput() override;
    void update() override;
    void render() override;
};

#endif
