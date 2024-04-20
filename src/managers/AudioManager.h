#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();
    void loadSound(const std::string &name, const std::string &filename);
    void playSound(const std::string &name);
    void clearSounds();

private:
    std::unordered_map<std::string, Mix_Chunk *> sounds;
};

#endif
