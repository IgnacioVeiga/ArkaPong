#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

// Structure to store texture data
struct Texture
{
    SDL_Texture *sdlTexture; // The actual SDL texture
    int width;               // Width of the texture
    int height;              // Height of the texture

    Texture(SDL_Texture *texture, int w, int h)
        : sdlTexture(texture), width(w), height(h) {}
};

#endif