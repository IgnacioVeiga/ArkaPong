#pragma once

#include <SDL2/SDL_mixer.h>

struct AudioComponent
{
    // For SFX
    Mix_Chunk* chunk;

    // For BGM
    Mix_Music* music;

    bool isPlaying;
    bool loop;
};
