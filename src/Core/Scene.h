#pragma once

#include "Camera.h"
#include "../Common.h"

struct Scene {
	std::vector<Camera> _cameras;

	void Init();
	void Update();
};