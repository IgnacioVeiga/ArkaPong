#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

class Entity
{
public:
    virtual ~Entity(){};
    virtual void render() = 0;

    // To get the rectangle of the entity to detect collisions
    virtual const SDL_Rect &getRect() const = 0;

protected:
    // Rectangle used for the position and the colider
    SDL_Rect rect;
};

#endif
