#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include "../entities/Texture.h"

class TextureManager
{
public:
    // Load a texture from a file and store it with a given ID
    static bool loadTexture(const std::string &id, const std::string &filename);

    // Draw a texture on the screen at (x, y) with optional clipping, flipping and scale
    static void drawTexture(
        const std::string &id,
        int x, int y,
        SDL_Rect *clip = nullptr,
        SDL_RendererFlip flip = SDL_FLIP_NONE
    );

    // Clear all loaded textures
    static void clearTextures();

    // Get a texture by its ID
    static Texture *getTexture(const std::string &id);

private:
    // Map to store textures by their IDs
    static std::unordered_map<std::string, Texture *> textures;
};

#endif