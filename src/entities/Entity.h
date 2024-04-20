#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

class Entity
{
public:
    virtual ~Entity() {}                             // Destructor virtual para permitir una eliminación adecuada
    virtual void move() = 0;                         // Función puramente virtual para mover la entidad
    virtual void render(SDL_Renderer *renderer) = 0; // Función puramente virtual para renderizar la entidad
    virtual const SDL_Rect &getRect() const = 0;     // Obtener el rectángulo de la entidad para detectar colisiones

protected:
    SDL_Rect rect;        // Posición y dimensiones de la entidad
    SDL_Texture *texture; // Textura de la entidad
};

#endif
