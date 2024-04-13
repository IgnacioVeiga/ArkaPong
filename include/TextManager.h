#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL_ttf.h>
#include <string>

class TextManager
{
public:
    TextManager(SDL_Renderer *renderer);
    ~TextManager();

    void loadFont(const std::string &fontPath, int fontSize);
    void displayText(const std::string &text, int x, int y, SDL_Color color);

private:
    TTF_Font *font = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif
