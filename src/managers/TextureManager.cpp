#include "TextureManager.h"
#include "Game.h"

SDL_Texture *TextureManager::LoadTexture(const char *filename)
{
    SDL_Surface *tempSurface = SDL_LoadBMP(filename);

    // Crear una textura a partir de la superficie
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);

    // Liberar la superficie después de crear la textura
    SDL_FreeSurface(tempSurface);

    return texture;
}