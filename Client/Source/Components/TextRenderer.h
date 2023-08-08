#pragma once
#include <string>
#include "SpriteRenderer.h"

class TextRenderer: public SpriteRenderer {
private:
	std::string _text;
	unsigned int _size{ 16 };

public:
	// Main Functions
	void SetText(std::string text, SDL_Color color = { 0, 0, 0 }, bool forceSet = false);
	void SetFontSize(unsigned int size);
	void CollectGarbage();

	~TextRenderer();
};