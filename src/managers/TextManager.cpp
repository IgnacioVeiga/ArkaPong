#include "TextManager.h"
#include "GameConstants.h"

TextManager::TextManager(SDL_Renderer *renderer) : renderer(renderer)
{
    font = TTF_OpenFont(FONT_FILEPATH, 16);
}

void TextManager::renderText(const std::string &text, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int text_width = surface->w;
    int text_height = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect renderQuad = {x, y, text_width, text_height};
    SDL_RenderCopy(renderer, texture, NULL, &renderQuad);
    SDL_DestroyTexture(texture);
}
