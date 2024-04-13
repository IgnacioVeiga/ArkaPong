#include "AudioManager.h"
#include <SDL2/SDL.h>

AudioManager::AudioManager()
{
    // Carga de sonidos
    sound_bounce = Mix_LoadWAV("sounds/bounce.wav");
    if (!sound_bounce)
    {
        SDL_Log("Failed to load bounce sound: %s", Mix_GetError());
    }

    sound_score = Mix_LoadWAV("sounds/score.wav");
    if (!sound_score)
    {
        SDL_Log("Failed to load score sound: %s", Mix_GetError());
    }

    sound_pause_start = Mix_LoadWAV("sounds/pause_start.wav");
    if (!sound_pause_start)
    {
        SDL_Log("Failed to load pause/start sound: %s", Mix_GetError());
    }
}

AudioManager::~AudioManager()
{
    Mix_FreeChunk(sound_bounce);
    Mix_FreeChunk(sound_score);
}

void AudioManager::playBounceSound()
{
    Mix_PlayChannel(-1, sound_bounce, 0); // Reproduce sonido de rebote
}

void AudioManager::playScoreSound()
{
    Mix_PlayChannel(-1, sound_score, 0); // Reproduce sonido de anotación
}

void AudioManager::playPauseStartSound()
{
    Mix_PlayChannel(-1, sound_pause_start, 0); // Reproduce sonido de anotación
}