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
    int channel = Mix_PlayChannelTimed(params.channel, sound, params.loops, params.ticks);
    if (channel != -1)
    {
        soundChannels[name] = channel; // Track the channel for this sound
    }

    if (params.wait)
    {
        // Wait for the sound to finish playing
        waitForSoundToFinish(name);
    }
}

void AudioManager::waitForSoundToFinish(const std::string &name)
{
    auto it = soundChannels.find(name);
    if (it != soundChannels.end())
    {
        int channel = it->second;
        while (Mix_Playing(channel) != 0)
        {
            SDL_Delay(100); // Wait 100 ms before checking again
        }
        soundChannels.erase(it); // Remove the channel from the tracking map
    }
    else
    {
        SDL_Log("Sound %s is not playing on any channel", name.c_str());
    }
}

void AudioManager::playSound(const std::string &name, bool wait)
{
    AudioParams params;
    params.wait = wait;
    playSound(name, params);
}

void AudioManager::playSound(const std::string &name, bool wait, int volume)
{
    AudioParams params;
    params.wait = wait;
    params.volume = volume;
    playSound(name, params);
}

void AudioManager::playSound(const std::string &name, bool wait, int volume, int loops, int ticks)
{
    AudioParams params;
    params.wait = wait;
    params.volume = volume;
    params.loops = loops;
    params.ticks = ticks;
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
