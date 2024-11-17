#pragma once

namespace Engine
{
	// Game Logic Functions
	void Initialize();
	void Update();
	void QuickKeys();

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