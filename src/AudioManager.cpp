#include <stdio.h>
#include "AudioManager.h"

// Definición de variables globales
Mix_Chunk *sound_bounce = NULL;
Mix_Chunk *sound_score = NULL;

bool loadMedia()
{
    // Cargando sonido de rebote
    sound_bounce = Mix_LoadWAV("sounds/bounce.wav");
    if (!sound_bounce)
    {
        printf("Failed to load bounce sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    // Cargando sonido de anotación
    sound_score = Mix_LoadWAV("sounds/score.wav");
    if (!sound_score)
    {
        printf("Failed to load score sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void closeAudio()
{
    Mix_FreeChunk(sound_bounce);
    Mix_FreeChunk(sound_score);
    sound_bounce = NULL;
    sound_score = NULL;
}
