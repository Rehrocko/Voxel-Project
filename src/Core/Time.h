#pragma once

namespace Time {
	extern double	lastFrame;
	extern double	thisFrame;
	extern double	deltaTimeAccumulator;
	extern double	deltaTime;

	void Init();
	void Update();
}