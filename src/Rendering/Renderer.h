#pragma once

#include "../Common.h"
#include "Shader.h"
#include "../Core/Scene.h"

namespace Renderer {
	void Init();
	void RenderFrame();
	void ReloadShaders();
	void DeveloperImGUI();

	// Developer Functions
	inline bool	displayFPS = true;
	inline bool	openDevMenu;
}