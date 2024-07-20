#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "../entities/Texture.h"

struct Animation
{
    std::vector<SDL_Rect> frames;
    int currentFrame;
    int speed; // Time per frame in milliseconds

    Animation() : currentFrame(0), speed(100) {}
    Animation(std::vector<SDL_Rect> frames, int speed) : frames(frames), currentFrame(0), speed(speed) {}
};

class TextureManager
{
public:
    // Load a texture from a file and store it with a given ID
    static bool loadTexture(const std::string &id, const std::string &filename);

    // Draw a texture on the screen at (x, y) with optional clipping, flipping and scale
    static void drawTexture(
        const std::string &id,
        SDL_Rect *dest_rect,
        SDL_Rect *src_rect = nullptr,
        SDL_RendererFlip flip = SDL_FLIP_NONE);

    // Clear all loaded textures
    static void clearTextures();

    // Get a texture by its ID
    static Texture *getTexture(const std::string &id);

    // Animation functions

    /*
        Using animations tutorial:

        // Load texture
        TextureManager::loadTexture("enemies", "assets/sprites/enemies.bmp");

        // Define frames for animation
        std::vector<SDL_Rect> framesRects = {
            {0, 0, 15, 15},
            {16, 0, 15, 15},
            {32, 0, 15, 15},
            {48, 0, 15, 15},
            {64, 0, 15, 15},
            {80, 0, 15, 15},
            {96, 0, 15, 15},
            {112, 0, 15, 15}
        };

        // Create animation
        TextureManager::createAnimation("enemies", "flying", framesRects, 100);

        // Render animation inside of game loop or render function
        SDL_Rect destRect = {100, 100, 15, 15}; // Position and size on screen
        TextureManager::playAnimation("enemies", "flying", &destRect);
    */
    static void createAnimation(const std::string &id, const std::string &animId, const std::vector<SDL_Rect> &frames, int speed);
    static void playAnimation(const std::string &id, const std::string &animId, SDL_Rect *dest_rect, SDL_RendererFlip flip = SDL_FLIP_NONE);
    static void clearAnimations();

private:
    // Map to store textures/animations by their IDs
    static std::unordered_map<std::string, Texture *> textures;
    static std::unordered_map<std::string, std::unordered_map<std::string, Animation>> animations;
    static Uint32 getTicks();
};

#endif
