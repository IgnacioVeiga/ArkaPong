#ifndef AUDIO_PARAMS_H
#define AUDIO_PARAMS_H

#include <string>
#include <SDL2/SDL_mixer.h>

struct AudioParams
{
    int volume = MIX_MAX_VOLUME;
    int loops = 0;    // 0 means play once, -1 means loop indefinitely
    int channel = -1; // -1 means play on the first available channel

    // Constructor with parameters for easier initialization if needed
    AudioParams(int volume = MIX_MAX_VOLUME, int loops = 0, int channel = -1)
        : volume(volume), loops(loops), channel(channel) {}
};

#endif
