#pragma once

#include "../../Game.h"
#include "../Coordinator.h"
#include "../Component/PositionComponent.h"
#include "../Component/MovementScriptComponent.h"
#include <chrono>

class MovementScriptSystem : public System
{
public:
	void Init()
	{
		Signature signature;
		signature.set(Game::coordinator.GetComponentType<PositionComponent>());
		signature.set(Game::coordinator.GetComponentType<MovementScriptComponent>());
		Game::coordinator.SetSystemSignature<MovementScriptSystem>(signature);
	}

	void Update()
	{
		using namespace std::chrono;
		// Get the current time
		auto now = steady_clock::now();
		// Calculate the deltaTime
		static auto lastTime = now;
		float deltaTime = duration_cast<duration<float>>(now - lastTime).count();
		lastTime = now;

		for (auto const& entity : mEntities)
		{
			auto& positionComponent = Game::coordinator.GetComponent<PositionComponent>(entity);
			auto& movementScriptComponent = Game::coordinator.GetComponent<MovementScriptComponent>(entity);

			// Update the position based on the movement script
			movementScriptComponent.script->UpdatePosition(positionComponent.x, positionComponent.y, deltaTime);

			for (const auto& event : movementScriptComponent.events)
			{
				if (positionComponent.x >= event.triggerX && positionComponent.y >= event.triggerY)
				{
					event.action(entity);
				}
			}
		}
	}
};