#pragma once

#include <iostream>
#include <unordered_map>

#if defined(_MSC_VER)
#include <SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif

class AudioManager {
public:
    static Mix_Chunk *LoadChunk(const std::string &path) {
        if (chunks.find(path) == chunks.end()) {
            Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
            if (!chunk) {
                std::cerr << "Error loading WAV: " << Mix_GetError() << std::endl;
            }
            chunks[path] = chunk;
        }
        return chunks[path];
    }

    static Mix_Music *LoadMusic(const std::string &path) {
        if (musics.find(path) == musics.end()) {
            Mix_Music *music = Mix_LoadMUS(path.c_str());
            if (!music) {
                std::cerr << "Error loading Music: " << Mix_GetError() << std::endl;
            }
            musics[path] = music;
        }
        return musics[path];
    }

    static void Cleanup() {
        for (const auto &pair: chunks) {
            Mix_FreeChunk(pair.second);
        }
        chunks.clear();

        for (const auto &pair: musics) {
            Mix_FreeMusic(pair.second);
        }
        musics.clear();
    }

private:
    static std::unordered_map<std::string, Mix_Chunk *> chunks;
    static std::unordered_map<std::string, Mix_Music *> musics;
};

std::unordered_map<std::string, Mix_Chunk *> AudioManager::chunks;
std::unordered_map<std::string, Mix_Music *> AudioManager::musics;
