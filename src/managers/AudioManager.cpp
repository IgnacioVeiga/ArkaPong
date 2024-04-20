#include "AudioManager.h"
#include <SDL2/SDL.h>

AudioManager::AudioManager() {}

AudioManager::~AudioManager()
{
    clearSounds();
}

void AudioManager::loadSound(const std::string &name, const std::string &filename)
{
    Mix_Chunk *sound = Mix_LoadWAV(filename.c_str());
    if (sound)
    {
        sounds[name] = sound;
    }
    else
    {
        SDL_Log("Failed to load sound %s: %s", filename.c_str(), Mix_GetError());
    }
}

void AudioManager::playSound(const std::string &name)
{
    Mix_PlayChannel(-1, sounds[name], 0);
}

void AudioManager::clearSounds()
{
    for (auto &kv : sounds)
    {
        Mix_FreeChunk(kv.second);
    }
    sounds.clear();
}
