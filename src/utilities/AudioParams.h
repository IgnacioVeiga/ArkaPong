#ifndef AUDIO_PARAMS_H
#define AUDIO_PARAMS_H

#include <string>
#include <SDL2/SDL_mixer.h>

struct AudioParams
{
    int volume = MIX_MAX_VOLUME;

    // 0 means play once, -1 means loop indefinitely
    int loops = 0;

    // -1 means play on the first available channel
    int channel = -1;

    // Maximum number of milliseconds to play this chunk before halting it. To play until all data has been mixed, specify -1.
    int ticks = -1;

    // Constructor with parameters for easier initialization if needed
    AudioParams(int channel = -1, int volume = MIX_MAX_VOLUME, int loops = 0, int ticks = -1)
        : channel(channel), volume(volume), loops(loops), ticks(ticks) {}
};

#endif
