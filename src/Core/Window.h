#pragma once

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <vector>
#include "Utils/CoreConstants.h"

struct Resolution {
	int width;
	int height;
};

class Window
{
public:
	bool Init();
	void CleanUp();
	void SetWindowMode(int resolutionIndex, Uint32 flags);

	SDL_Window* GetWindow() const { return window; }
	SDL_Renderer* GetRenderer() const { return renderer; }

	std::vector<Resolution> availableResolutions = {
		{SCREEN_WIDTH, SCREEN_HEIGHT},  // Logic resolution
		{1280, 720},					// HD
		{1920, 1080},					// Full HD
		{2560, 1440},					// 2K
		{3840, 2160}					// 4K
	};

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};
