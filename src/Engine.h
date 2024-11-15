#pragma once

#include "Rendering/Shader.h"
#include "Core/GL.h"
#include "Core/Time.h"
#include "Core/Input.h"

namespace Engine
{
	// Game Logic Functions
	void Initialize();
	void Update();

	// Developer Functions
	inline bool	displayFPS = true;
	inline bool	openDevMenu;
	void DeveloperImGUI();

	enum class GAMESTATE {
		FREECAM,
		PAUSED,
		MENU,
	};
}