#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

class TextManager {
public:
    TextManager();
    ~TextManager();
    void renderText(const std::string &text, int x, int y, SDL_Color color = {255, 255, 255, 255});
    void clearTextCache();

private:
    TTF_Font *font;
    std::unordered_map<std::string, SDL_Texture*> textCache;
};

#endif
