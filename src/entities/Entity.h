#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

class Entity
{
public:
    virtual ~Entity(){};
    virtual void move() = 0;
    virtual void render() = 0;

    // To get the rectangle of the entity to detect collisions
    virtual const SDL_Rect &getRect() const = 0;

protected:
    SDL_Rect rect;
    SDL_Texture *texture;
};

#endif
