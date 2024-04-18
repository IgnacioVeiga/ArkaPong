#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextManager
{
public:
    TextManager(SDL_Renderer *renderer);
    void renderText(const std::string &text, int x, int y, SDL_Color color = {255, 255, 255, 255});

private:
    SDL_Renderer *renderer;
    TTF_Font *font;
};

#endif
