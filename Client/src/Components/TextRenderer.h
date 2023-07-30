#pragma once
#include <string>
#include "SpriteRenderer.h"
#include "../UI/UIElement.h"

class TextRenderer: public SpriteRenderer {
private:
	SpriteRenderer outlineRenderer{};

	std::string _text;
	SDL_Color _color{ 0, 0, 0 };
	SDL_Color _outlineColor{ 0, 0, 0 };
	unsigned int _size{ 16 };
	unsigned int _outlineSize{ 0 };

public:
	// Constructor
	TextRenderer();

	// Base Functions
	void Render() override;

	// Main Functions
	void SetText(std::string text, SDL_Color color = { 0, 0, 0 }, bool forceSet = false);
	void SetOutlineText(SDL_Color color = { 255, 255, 255 }, unsigned int outlineSize = 3);
	void SetFontSize(unsigned int size);
	void CollectGarbage();
};