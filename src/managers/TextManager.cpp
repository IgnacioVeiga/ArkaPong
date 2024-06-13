#include "TextManager.h"
#include "../Game.h"

TextManager::~TextManager() {
    clearTextCache();
    for (auto& fontSet : fonts) {
        for (auto& font : fontSet.second) {
            TTF_CloseFont(font.second);
        }
    }
}

TTF_Font* TextManager::loadFont(const std::string& fontPath, int fontSize) {
    if (fonts[fontPath].find(fontSize) == fonts[fontPath].end()) {
        TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
            return nullptr;
        }
        fonts[fontPath][fontSize] = font;
    }
    return fonts[fontPath][fontSize];
}

SDL_Texture* TextManager::createTextTexture(const std::string& text, const TextParams& params) {
    std::string cacheKey = text + std::to_string(params.fontSize) + params.fontPath;
    SDL_Texture* texture = textCache[cacheKey];
    if (!texture) {
        TTF_Font* font = loadFont(params.fontPath, params.fontSize);
        if (!font) return nullptr;

        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), params.color);
        if (!surface) {
            SDL_Log("Failed to create text surface: %s", TTF_GetError());
            return nullptr;
        }

        texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
        SDL_FreeSurface(surface);

        textCache[cacheKey] = texture;
    }
    return texture;
}

void TextManager::renderText(const std::string& text, const TextParams& params) {
    SDL_Texture* texture = createTextTexture(text, params);
    if (!texture) return;

    int text_width, text_height;
    SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height);

    int x = params.x;
    if (params.alignment == TextAlignment::CENTER) {
        x -= text_width / 2;
    }
    else if (params.alignment == TextAlignment::RIGHT) {
        x -= text_width;
    }

    SDL_Rect renderQuad = { x, params.y, text_width, text_height };
    SDL_RenderCopy(Game::renderer, texture, NULL, &renderQuad);

    // TODO: Handle animation or other effects if params.animated is true
}

void TextManager::renderText(const std::string& text, int x, int y) {
    TextParams params;
    params.x = x;
    params.y = y;
    renderText(text, params);
}

void TextManager::renderText(const std::string& text, int x, int y, SDL_Color color) {
    TextParams params;
    params.x = x;
    params.y = y;
    params.color = color;
    renderText(text, params);
}

void TextManager::renderText(const std::string& text, int x, int y, SDL_Color color, TextAlignment alignment) {
    TextParams params;
    params.x = x;
    params.y = y;
    params.color = color;
    params.alignment = alignment;
    renderText(text, params);
}

void TextManager::renderText(const std::string& text, int x, int y, SDL_Color color, TextAlignment alignment, int fontSize) {
    TextParams params;
    params.x = x;
    params.y = y;
    params.color = color;
    params.alignment = alignment;
    params.fontSize = fontSize;
    renderText(text, params);
}

void TextManager::renderText(const std::string& text, int x, int y, TextAlignment alignment) {
    TextParams params;
    params.x = x;
    params.y = y;
    params.alignment = alignment;
    renderText(text, params);
}

void TextManager::renderText(const std::string& text, int x, int y, TextAlignment alignment, int fontSize) {
    TextParams params;
    params.x = x;
    params.y = y;
    params.alignment = alignment;
    params.fontSize = fontSize;
    renderText(text, params);
}

void TextManager::clearTextCache() {
    for (auto& kv : textCache) {
        SDL_DestroyTexture(kv.second);
    }
    textCache.clear();
}
