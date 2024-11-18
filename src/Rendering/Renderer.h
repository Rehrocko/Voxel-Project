#pragma once

#include "../Common.h"
#include "Shader.h"
#include "../Core/Scene.h"
#include "../Core/Chunk.h"

namespace Renderer {
	void Init();
	void RenderFrame();
	void ReloadShaders();
	void DeveloperImGUI();

	inline Chunk chunk;

	// Developer Functions
	inline bool	displayFPS = true;
	inline bool	openDevMenu = true;
	inline bool showUI = true;
}