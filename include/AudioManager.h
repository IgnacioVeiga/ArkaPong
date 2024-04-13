#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <SDL2/SDL_mixer.h>

// Declaración de variables globales para los efectos de sonido
extern Mix_Chunk *sound_bounce;
extern Mix_Chunk *sound_score;

bool loadMedia();  // Función para cargar los medios
void closeAudio(); // Función para liberar recursos de audio

#endif
