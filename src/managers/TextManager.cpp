#include "TextManager.h"
#include <Game.h>

TextManager::TextManager()
{
    font = TTF_OpenFont("assets/fonts/PressStart2P-vaV7.ttf", 16);
    if (!font)
    {
        SDL_Log("Failed to load font: %s", TTF_GetError());
    }
}

TextManager::~TextManager()
{
    TTF_CloseFont(font);
    clearTextCache();
}

void TextManager::renderText(const std::string &text, int x, int y, SDL_Color color)
{
    SDL_Texture *texture = textCache[text];
    if (!texture)
    {
        SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        textCache[text] = texture;
        SDL_FreeSurface(surface);
    }
    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);
    SDL_Rect renderQuad = {x, y, text_width, text_height};
    SDL_RenderCopy(Game::renderer, texture, NULL, &renderQuad);
}

void TextManager::clearTextCache()
{
    for (auto &kv : textCache)
    {
        SDL_DestroyTexture(kv.second);
    }
    textCache.clear();
}
