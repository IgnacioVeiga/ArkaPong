#pragma once

#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/TextComponent.h"

class TextSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<TextComponent>());
		Game::coordinator.SetSystemSignature<TextSystem>(signature);
	}

	void Update()
	{
		for (auto const& entity : mEntities)
		{
			auto& textComponent = Game::coordinator.GetComponent<TextComponent>(entity);

			if (textComponent.dirty)
			{
				UpdateTexture(textComponent);
				textComponent.dirty = false;
			}

			if (textComponent.texture)
			{
				SDL_Rect renderRect = GetAlignedRect(entity, textComponent);
				SDL_RenderCopy(
					Game::window.GetRenderer(),		// Renderer
					textComponent.texture,			// Texture
					NULL,							// Source rectangle
					&renderRect						// Destination Rectangle
				);
			}
		}
	}

private:
	void UpdateTexture(TextComponent& textComponent)
	{
		if (textComponent.texture)
		{
			SDL_DestroyTexture(textComponent.texture);
		}

		SDL_Surface* surface = TTF_RenderText_Solid(
			textComponent.font,         // Font
			textComponent.text.c_str(), // Text
			textComponent.color         // Color
		);

		if (!surface)
		{
			std::cerr << "Error creating text surface: " << TTF_GetError() << std::endl;
			textComponent.texture = nullptr;
			return;
		}

		textComponent.texture = SDL_CreateTextureFromSurface(Game::window.GetRenderer(), surface);

		if (!textComponent.texture)
		{
			std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
		}

		SDL_FreeSurface(surface);
	}

	SDL_Rect GetAlignedRect(Entity entity, TextComponent& textComponent)
	{
		SDL_Rect renderRect{ 0, 0, 0, 0 };
		SDL_QueryTexture(textComponent.texture, NULL, NULL, &renderRect.w, &renderRect.h);

		// Check if the entity has a TransformComponent
		Vec2 finalPosition = textComponent.position;
		if (Game::coordinator.HasComponent<TransformComponent>(entity))
		{
			auto& transform = Game::coordinator.GetComponent<TransformComponent>(entity);
			finalPosition = transform.position + textComponent.position; // Add relative position
		}

		renderRect.x = finalPosition.x;
		renderRect.y = finalPosition.y;

		// Handle alignment
		switch (textComponent.alignment)
		{
		case Side::CENTER:
			renderRect.x -= renderRect.w / 2;
			break;
		case Side::RIGHT:
			renderRect.x -= renderRect.w;
			break;
		case Side::LEFT:
		default:
			break;
		}

		return renderRect;
	}
};
