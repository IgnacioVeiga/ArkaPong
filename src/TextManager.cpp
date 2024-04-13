#include "TextManager.h"

TextManager::TextManager(SDL_Renderer *renderer) : renderer(renderer)
{
    TTF_Init();
}

TextManager::~TextManager()
{
    if (font)
    {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

void TextManager::loadFont(const std::string &fontPath, int fontSize)
{
    font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
    }
}

void TextManager::displayText(const std::string &text, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dest = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dest);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
