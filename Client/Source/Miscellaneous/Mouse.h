#pragma once
#include <SDL_mouse.h>
#include "Core/Miscellaneous/Vector.h"

class Mouse {
public:
	static Vector2 GetPosition() {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		return Vector2((float)mouseX, (float)mouseY);
	}
};