#include "Time.h"
float Time::deltaTime = 1 / Time::MAX_FPS;
float Time::frameTime = 16.66f;
const float Time::fixedDeltaTime = 1 / Time::MAX_FPS;
const unsigned int FRAME_DELAY = 1000 / Time::MAX_FPS;