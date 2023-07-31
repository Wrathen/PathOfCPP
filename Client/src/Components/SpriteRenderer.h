#pragma once
#include <SDL_image.h>
#include "Transform.h"

class SpriteRenderer { friend class Renderer;
public:
	typedef SpriteRenderer Super;

	Transform* transform = nullptr;
	SDL_Texture* tex = nullptr;

	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Color color = {255, 255, 255};
	SDL_Color shadowColor = {0, 0, 0};

	Vector2 sourceOffset;
	Vector2 offset;
	Vector2 localScale{ 1.0f, 1.0f };

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
	void SetColor(SDL_Color _color);
	void SetShadow(unsigned int _size, SDL_Color _shadowColor);

	virtual void Render();

	// Setters
	void SetSourceOffset(int x, int y);
	void SetSourceOffset(const Vector2& vec);
	void SetOffset(int x, int y);
	void SetOffset(const Vector2& vec);
	void SetWidth(unsigned int _w);
	void SetHeight(unsigned int _h);
	void SetScale(float x, float y);
	void SetScale(const Vector2& vec);
	void SetVisible(bool flag);

	// Getters
	Vector2& GetOffset();
	unsigned int GetWidth();
	unsigned int GetHeight();
	bool GetVisible();

protected:
	// Shadows, currently used only by TextRenderer.
	bool isShadowEnabled = false;
	unsigned int shadowSize = 0;

	virtual void SetSourceAndDestinationRects();
};