#pragma once

#include "Coordinator.h"
#include "Manager/SceneManager.h"
#include "Window.h"

namespace Core
{
	static Coordinator coordinator;
	static SceneManager scene_manager;
	static Window window;
	bool game_on = true;
}