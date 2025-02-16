#include "Window.h"

#include <SDL2/SDL.h>

#if defined(_MSC_VER)
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#else
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <iostream>

bool Window::Init(const char* title)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return false;
	if (TTF_Init() == -1)
		return false;
	if (Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		return false;

	Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
	if (!window)
		return false;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
		return false;

	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	return true;
}

void Window::CleanUp()
{
	if (renderer)
		SDL_DestroyRenderer(renderer);
	if (window)
		SDL_DestroyWindow(window);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

// TODO: fix fullscreen mode in Linux, not working on KDE
void Window::SetWindowMode(int resolutionIndex, Uint32 flags)
{
	if (resolutionIndex < 0 || resolutionIndex >= availableResolutions.size())
	{
		std::cerr << "Invalid resolution index" << std::endl;
		return;
	}

	int width = availableResolutions[resolutionIndex].width;
	int height = availableResolutions[resolutionIndex].height;

	SDL_SetWindowSize(window, width, height);
	SDL_SetWindowFullscreen(window, flags);
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

//#ifdef __linux__
//	SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
//#endif
}
