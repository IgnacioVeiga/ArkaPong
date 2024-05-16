#include "TextureManager.h"
#include "Game.h"

SDL_Texture *TextureManager::LoadTexture(const char *filename)
{
    SDL_Surface *tempSurface = SDL_LoadBMP(filename);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}