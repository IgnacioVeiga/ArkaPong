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
    void playPauseStartSound();

private:
    Mix_Chunk *sound_bounce;
    Mix_Chunk *sound_score;
    Mix_Chunk *sound_pause_start;
};

#endif