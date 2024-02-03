#pragma once
#include <ctime>

struct Time {
	// Maximum Frames Per Second
	static inline const int MAX_FPS = 144;

	// The time it took to render the previous frame.	
	static inline double frameTime = 1000 / MAX_FPS;

	// Delta time, this should be updated from an external source. (GameManagers)
	static inline double deltaTime = 1 / Time::MAX_FPS;

	// Fixed Delta time. Never changes.
	static constexpr inline const double fixedDeltaTime = 1 / Time::MAX_FPS;

	// Delay between each frames based on maximum frames per second.
	static constexpr inline const unsigned int FRAME_DELAY = 1000 / MAX_FPS;

	static inline long long GetTime() { return std::time(0); }
};