#include "TextureManager.h"
#include "../Game.h"
#include <iostream>
#include "../utilities/GameConstants.h"

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

void TextureManager::drawTexture(const std::string &id, SDL_Rect *dest_rect, SDL_Rect *src_rect, SDL_RendererFlip flip)
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
    int scaledWidth = static_cast<int>(tex->width * SCALE);
    int scaledHeight = static_cast<int>(tex->height * SCALE);

    // If a clip rectangle is provided, adjust the rendering rectangle's size
    if (src_rect)
    {
        dest_rect->w = src_rect->w * SCALE;
        dest_rect->h = src_rect->h * SCALE;
    }
    else
    {
        // Set the rendering rectangle with scaled dimensions
        dest_rect->h = scaledWidth;
        dest_rect->h = scaledHeight;
    }

    // Render the texture with optional clipping, flipping, and scaling
    SDL_RenderCopyEx(Game::renderer, tex->sdlTexture, src_rect, dest_rect, 0.0, nullptr, flip);
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
