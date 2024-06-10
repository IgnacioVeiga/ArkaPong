#include "TextureManager.h"
#include "../Game.h"
#include <iostream>

// Initialize the static member variable
std::unordered_map<std::string, Texture *> TextureManager::textures;

bool TextureManager::loadTexture(const std::string &id, const std::string &filename)
{
    // Load the BMP image into an SDL_Surface
    SDL_Surface *tempSurface = SDL_LoadBMP(filename.c_str());
    if (!tempSurface)
    {
        // Log an error if the image fails to load
        SDL_Log("Failed to load BMP %s: %s", filename.c_str(), SDL_GetError());
        return false;
    }

    // Create an SDL_Texture from the SDL_Surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (!texture)
    {
        // Log an error if the texture fails to create
        SDL_Log("Failed to create texture from %s: %s", filename.c_str(), SDL_GetError());
        SDL_FreeSurface(tempSurface);
        return false;
    }

    // Create a Texture object to store the texture and its dimensions
    Texture *tex = new Texture(texture, tempSurface->w, tempSurface->h);
    textures[id] = tex; // Store the texture in the map with the given ID

    // Free the SDL_Surface now that we have the texture
    SDL_FreeSurface(tempSurface);
    return true;
}

void TextureManager::drawTexture(const std::string &id, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip, double scaleX, double scaleY)
{
    // Find the texture in the map by its ID
    auto it = textures.find(id);
    if (it == textures.end())
    {
        // Log an error if the texture is not found
        SDL_Log("Texture %s not found", id.c_str());
        return;
    }

    Texture *tex = it->second; // Get the texture from the map

    // Calculate the scaled width and height of the texture
    int scaledWidth = static_cast<int>(tex->width * scaleX);
    int scaledHeight = static_cast<int>(tex->height * scaleY);

    SDL_Rect renderQuad = {x, y, scaledWidth, scaledHeight}; // Set the rendering rectangle with scaled dimensions

    // If a clip rectangle is provided, adjust the rendering rectangle's size
    if (clip)
    {
        renderQuad.w = clip->w * scaleX;
        renderQuad.h = clip->h * scaleY;
    }

    // Render the texture with optional clipping, rotation, flipping, and scaling
    SDL_RenderCopyEx(Game::renderer, tex->sdlTexture, clip, &renderQuad, angle, center, flip);
}

void TextureManager::clearTextures()
{
    // Iterate through all textures in the map and destroy them
    for (auto &kv : textures)
    {
        SDL_DestroyTexture(kv.second->sdlTexture);
        delete kv.second; // Delete the Texture object
    }
    textures.clear(); // Clear the map
}

Texture *TextureManager::getTexture(const std::string &id)
{
    // Find the texture in the map by its ID
    auto it = textures.find(id);
    if (it != textures.end())
    {
        return it->second; // Return the texture if found
    }
    return nullptr; // Return nullptr if the texture is not found
}
