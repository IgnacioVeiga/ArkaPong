#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>
#include "../utilities/AudioParams.h"

class AudioManager
{
public:
    ~AudioManager();

    void loadSound(const std::string &name, const std::string &filename);
    void playSound(const std::string &name, const AudioParams &params = AudioParams());

    // Overloads for partial customization
    void playSound(const std::string &name, int volume);
    void playSound(const std::string &name, int volume, int loops);

    void pauseAllSounds();
    void resumeAllSounds();
    void pauseSound(const std::string &name);
    void resumeSound(const std::string &name);

    void clearSounds();

private:
    std::unordered_map<std::string, Mix_Chunk *> sounds;
    std::unordered_map<std::string, int> soundChannels; // Track channels per sound
};

#endif
