#include "AudioManager.h"
#include <SDL2/SDL.h>

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

void AudioManager::playSound(const std::string &name, const AudioParams &params)
{
    auto it = sounds.find(name);
    if (it == sounds.end())
    {
        SDL_Log("Sound %s not found", name.c_str());
        return;
    }

    Mix_Chunk *sound = it->second;
    Mix_VolumeChunk(sound, params.volume);
    int channel = Mix_PlayChannel(params.channel, sound, params.loops);
    if (channel != -1)
    {
        soundChannels[name] = channel; // Track the channel for this sound
    }
}

void AudioManager::playSound(const std::string &name, int volume)
{
    AudioParams params;
    params.volume = volume;
    playSound(name, params);
}

void AudioManager::playSound(const std::string &name, int volume, int loops)
{
    AudioParams params;
    params.volume = volume;
    params.loops = loops;
    playSound(name, params);
}

void AudioManager::pauseAllSounds()
{
    Mix_Pause(-1); // -1 means pause all channels
}

void AudioManager::resumeAllSounds()
{
    Mix_Resume(-1); // -1 means resume all channels
}

void AudioManager::pauseSound(const std::string &name)
{
    auto it = soundChannels.find(name);
    if (it != soundChannels.end())
    {
        Mix_Pause(it->second);
    }
    else
    {
        SDL_Log("Sound %s is not currently playing", name.c_str());
    }
}

void AudioManager::resumeSound(const std::string &name)
{
    auto it = soundChannels.find(name);
    if (it != soundChannels.end())
    {
        Mix_Resume(it->second);
    }
    else
    {
        SDL_Log("Sound %s is not currently paused", name.c_str());
    }
}

void AudioManager::clearSounds()
{
    for (auto &kv : sounds)
    {
        Mix_FreeChunk(kv.second);
    }
    sounds.clear();
    soundChannels.clear();
}
