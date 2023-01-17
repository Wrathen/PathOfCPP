#pragma once
#include <string>
#include "SpriteRenderer.h"

class TextRenderer: public SpriteRenderer {
private:
	std::string _text;
	SDL_Color _color;
	unsigned int _size;

public:
	void SetText(std::string text, SDL_Color color);
	void SetFontSize(unsigned int size);
	void CollectGarbage();
	~TextRenderer();
};