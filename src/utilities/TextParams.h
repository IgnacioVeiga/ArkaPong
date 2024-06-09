#ifndef TEXTPARAMS_H
#define TEXTPARAMS_H

#include <SDL2/SDL.h>
#include <string>

enum class TextAlignment { LEFT, CENTER, RIGHT };

struct TextParams {
	std::string fontPath = "assets/fonts/PressStart2P-vaV7.ttf";
	int fontSize = 16;
	SDL_Color color = { 255, 255, 255, 255 };
	int x = 0;
	int y = 0;
	TextAlignment alignment = TextAlignment::LEFT;
	bool animated = false;

	// Constructor with parameters for easier initialization if needed
	TextParams(const std::string& fontPath = "assets/fonts/PressStart2P-vaV7.ttf",
		int fontSize = 16,
		SDL_Color color = { 255, 255, 255, 255 },
		int x = 0,
		int y = 0,
		TextAlignment alignment = TextAlignment::LEFT,
		bool animated = false)
		: fontPath(fontPath), fontSize(fontSize), color(color), x(x), y(y), alignment(alignment), animated(animated) {}
};

#endif