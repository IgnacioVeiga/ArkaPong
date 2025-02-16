#pragma once

#include <SDL2/SDL_render.h>

struct ImageBackgroundComponent {
	SDL_Texture* imageTexture;
	int width;
	int height;
};