#pragma once

#include <SDL2/SDL.h>

struct ParallaxLayer {
	SDL_Texture* layerTexture;
	float scrollSpeed;
};
