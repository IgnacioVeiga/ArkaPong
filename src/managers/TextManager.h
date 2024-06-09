#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <memory>
#include "../utilities/TextParams.h"

class TextManager {
public:
    ~TextManager();

    void renderText(const std::string& text, const TextParams& params = TextParams());

    // Overloads for partial customization
    void renderText(const std::string& text, int x, int y);

    void renderText(const std::string& text, int x, int y, TextAlignment alignment);
    void renderText(const std::string& text, int x, int y, TextAlignment alignment, int fontSize);
    void renderText(const std::string& text, int x, int y, SDL_Color color);
    void renderText(const std::string& text, int x, int y, SDL_Color color, TextAlignment alignment);
    void renderText(const std::string& text, int x, int y, SDL_Color color, TextAlignment alignment, int fontSize);

    void clearTextCache();

private:
    TTF_Font* loadFont(const std::string& fontPath, int fontSize);
    SDL_Texture* createTextTexture(const std::string& text, const TextParams& params);

    std::unordered_map<std::string, std::unordered_map<int, TTF_Font*>> fonts;
    std::unordered_map<std::string, SDL_Texture*> textCache;
};

#endif