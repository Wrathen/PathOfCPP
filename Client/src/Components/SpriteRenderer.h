#pragma once
#include <SDL_image.h>
#include "Transform.h"

class SpriteRenderer { friend class Renderer;
public:
	Transform* transform = nullptr;
	SDL_Texture* tex = nullptr;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	Vector2 sourceOffset;
	Vector2 offset;

	unsigned int width = 32;
	unsigned int height = 32;

	bool isFlipped = false;
	bool isVisible = true;
	bool isAbsolutePositioned = false;
	bool shouldDrawCentered = false;

	// Main Functions
	void AssignTexture(SDL_Texture* _tex);
	void AssignTexture(std::string path);
	void AssignTransform(Transform* _transform);
	void UpdateTextureDimensions();

	void SetPositionAbsolute();
	void SetPositionRelative();
	void SetColor(int r, int g, int b);

	void Render();

	// Setters
	void SetSourceOffset(int x, int y);
	void SetSourceOffset(const Vector2& vec);
	void SetOffset(int x, int y);
	void SetOffset(const Vector2& vec);
	void SetWidth(unsigned int _w);
	void SetHeight(unsigned int _h);
	void SetVisible(bool flag);

	// Getters
	Vector2& GetOffset();
	unsigned int GetWidth();
	unsigned int GetHeight();
	bool GetVisible();

protected:
	virtual void SetSourceAndDestinationRects();
};