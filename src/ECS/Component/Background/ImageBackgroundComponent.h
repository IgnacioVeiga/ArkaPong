#pragma once

#include <SDL2/SDL.h>

struct ImageBackgroundComponent {
	SDL_Texture* imageTexture;
	int width;
	int height;
};