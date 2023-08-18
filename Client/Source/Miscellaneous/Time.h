#pragma once

struct Time {
	static float deltaTime;
	static const float fixedDeltaTime;
	static float frameTime;

	static const int MAX_FPS = 144;
	static const unsigned int FRAME_DELAY = 1000 / MAX_FPS;
};