#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SDL2/SDL_mixer.h>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager();
    void playBounceSound();
    void playScoreSound();

private:
    Mix_Chunk *sound_bounce;
    Mix_Chunk *sound_score;
};

#endif