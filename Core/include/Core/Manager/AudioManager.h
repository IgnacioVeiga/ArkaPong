#pragma once

#include <unordered_map>

#if defined(_MSC_VER)
#include <SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif

class AudioManager {
public:
    static Mix_Chunk *LoadChunk(const std::string &path);
    static Mix_Music *LoadMusic(const std::string &path);
    static void Cleanup();
private:
    static std::unordered_map<std::string, Mix_Chunk *> chunks;
    static std::unordered_map<std::string, Mix_Music *> musics;
};
