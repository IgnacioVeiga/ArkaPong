#pragma once

#include <SDL_ttf.h>
#include <iostream>

class TextSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Core::coordinator.GetComponentType<TextComponent>());
		Core::coordinator.SetSystemSignature<TextSystem>(signature);
	}

	void Update()
	{
		for (auto const& entity : mEntities)
		{
			auto& textComponent = Core::coordinator.GetComponent<TextComponent>(entity);

			if (textComponent.dirty)
			{
				UpdateTexture(textComponent);
				textComponent.dirty = false;
			}

			if (textComponent.texture)
			{
				SDL_Rect renderRect = GetAlignedRect(entity, textComponent);
				SDL_RenderCopy(
					Core::window.GetRenderer(),		// Renderer
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

		textComponent.texture = SDL_CreateTextureFromSurface(Core::window.GetRenderer(), surface);

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
		if (Core::coordinator.HasComponent<TransformComponent>(entity))
		{
			auto& transform = Core::coordinator.GetComponent<TransformComponent>(entity);
			finalPosition = transform.position + textComponent.position; // Add relative position
		}

		renderRect.x = static_cast<int>(finalPosition.x);
		renderRect.y = static_cast<int>(finalPosition.y);

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
