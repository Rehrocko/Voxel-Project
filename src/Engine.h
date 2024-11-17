#pragma once

#include "Core/Scene.h"

namespace Engine
{
	// Game Logic Functions
	void Initialize();
	void Update();
	void QuickKeys();

	enum class GAMESTATE {
		FREECAM,
		PAUSED,
		MENU,
	};

	inline std::vector<Scene> _scenes = { Scene() };

	// mainScene really just means working scene, I also just wanted to have a vector of
	// scenes in case I ever needed it, we basically only use mainScene
	inline Scene& mainScene = _scenes[0];

}