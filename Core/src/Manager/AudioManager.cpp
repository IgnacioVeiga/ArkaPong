#include <iostream>
#include <unordered_map>

#include "Core/Manager/AudioManager.h"

Mix_Chunk* AudioManager::LoadChunk(const std::string& path)
{
    if (chunks.find(path) == chunks.end())
    {
        Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());
        if (!chunk)
        {
            std::cerr << "Error loading WAV '" << path << "': " << Mix_GetError() << std::endl;
        }
        chunks[path] = chunk;
    }
    return chunks[path];
}

Mix_Music* AudioManager::LoadMusic(const std::string& path)
{
    if (musics.find(path) == musics.end())
    {
        Mix_Music* music = Mix_LoadMUS(path.c_str());
        if (!music)
        {
            std::cerr << "Error loading Music '" << path << "': " << Mix_GetError() << std::endl;
        }
        musics[path] = music;
    }
    return musics[path];
}

void AudioManager::Cleanup()
{
    for (const auto& [key, value] : chunks)
    {
        Mix_FreeChunk(value);
    }
    chunks.clear();

    for (const auto& [key, value] : musics)
    {
        Mix_FreeMusic(value);
    }
    musics.clear();
}

std::unordered_map<std::string, Mix_Chunk *> AudioManager::chunks;
std::unordered_map<std::string, Mix_Music *> AudioManager::musics;
