#pragma once
#include "Vector.h"

class Mouse {
public:
	static Vector2 GetPosition() {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);
		return Vector2(mouseX, mouseY);
	}
};