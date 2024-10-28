#pragma once

#include "Coordinator.h"
#include "Manager/SceneManager.h"
#include "Window.h"

namespace Game
{
	static Coordinator coordinator;
	static SceneManager scene_manager;
	static Window window;
	bool game_on = true;
}