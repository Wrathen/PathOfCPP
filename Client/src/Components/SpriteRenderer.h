#pragma once
#include <SDL_image.h>
#include "../Miscellaneous/GUID.h"
#include "Transform.h"

class SpriteRenderer {
	friend class Renderer;
public:
	void SetOffset(int x, int y) { offset.x = x; offset.y = y; }
	void SetOffset(const Vector2& vec) { offset.x = vec.x; offset.y = vec.y; }
	void SetWidth(unsigned int _w) { width = _w; }
	void SetHeight(unsigned int _h) { height = _h; }
	void SetVisible(bool flag);
	void AssignTexture(SDL_Texture* _tex);
	void AssignTexture(std::string path);
	void AssignTransform(Transform* _transform);
	void UpdateTextureDimensions();

	void SetPositionAbsolute();
	void SetPositionRelative();

	void Render();

	Transform* transform = nullptr;
	SDL_Texture* tex = nullptr;

	Vector2 offset;
	unsigned int width = 32;
	unsigned int height = 32;

	bool isVisible = true;
	bool isAbsolutePositioned = false;
	bool shouldDrawCentered = false;
};