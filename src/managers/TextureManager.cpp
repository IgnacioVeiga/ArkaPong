#include "TextureManager.h"
#include "../Game.h"
#include <iostream>
#include "../utilities/GameConstants.h"

std::unordered_map<std::string, Texture *> TextureManager::textures;
std::unordered_map<std::string, std::unordered_map<std::string, Animation>> TextureManager::animations;

bool TextureManager::loadTexture(const std::string &id, const std::string &filename)
{
    // Load the BMP image into an SDL_Surface
    SDL_Surface *tempSurface = SDL_LoadBMP(filename.c_str());
    if (!tempSurface)
    {
        SDL_Log("Failed to load BMP %s: %s", filename.c_str(), SDL_GetError());
        return false;
    }

    // Create an SDL_Texture from the SDL_Surface
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (!texture)
    {
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
        SDL_Log("Texture %s not found", id.c_str());
        return;
    }

    Texture *tex = it->second; // Get the texture from the map

    // Calculate the scaled width and height of the texture
    int scaledWidth = static_cast<int>(tex->width * SCALE);
    int scaledHeight = static_cast<int>(tex->height * SCALE);

    // If a source rectangle is provided, adjust the rendering rectangle's size
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

// New functions for animations
void TextureManager::createAnimation(const std::string &id, const std::string &animId, const std::vector<SDL_Rect> &frames, int speed)
{
    animations[id][animId] = Animation(frames, speed);
}

void TextureManager::playAnimation(const std::string &id, const std::string &animId, SDL_Rect *dest_rect, SDL_RendererFlip flip)
{
    auto itTex = textures.find(id);
    if (itTex == textures.end())
    {
        SDL_Log("Texture %s not found", id.c_str());
        return;
    }

    auto itAnim = animations.find(id);
    if (itAnim == animations.end() || itAnim->second.find(animId) == itAnim->second.end())
    {
        SDL_Log("Animation %s not found for texture %s", animId.c_str(), id.c_str());
        return;
    }

    Animation &anim = itAnim->second[animId];
    Uint32 ticks = getTicks();
    anim.currentFrame = (ticks / anim.speed) % anim.frames.size();
    SDL_Rect *src_rect = &anim.frames[anim.currentFrame];

    drawTexture(id, dest_rect, src_rect, flip);
}

void TextureManager::clearAnimations()
{
    animations.clear();
}

// Helper function to get current ticks
Uint32 TextureManager::getTicks()
{
    return SDL_GetTicks();
}