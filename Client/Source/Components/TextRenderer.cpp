#include "TextRenderer.h"
#include "../Managers/RenderManager.h"
#include "../Miscellaneous/Log.h"

// Main Functions
void TextRenderer::SetText(std::string text, SDL_Color color, bool forceSet) {
	if (!forceSet && text == _text) return;
	CollectGarbage();

	_text = text;

	// Create a surface from the text and size, create a texture from it and assign it into the SpriteRenderer.
	SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(MainRenderer.GetFont(_size), _text.c_str(), {255, 255, 255}, 0);
	Super::AssignTexture(SDL_CreateTextureFromSurface(MainRenderer.renderer, surface));

	// If text is empty, the width and height comes back in billions. Set them back to 0.
	if (text.empty()) {
		SetWidth(0);
		SetHeight(0);
	}

	// Convert the color into grayscale and then invert it so we can colorize shadows according to the base color.
	float colorGrayscale = (color.r + color.g + color.b) / 255.0f / 3.0f;
	Uint8 colorGrayscaleInverted = (1.0f - colorGrayscale) * 255.0f;
	Uint8 shadowColor = colorGrayscaleInverted < 0.5f ? 255 : 0;

	// Set colors and shadows into SpriteRenderer base class.
	SetColor(color);
	SetShadow(6, {shadowColor, shadowColor, shadowColor});

	// Free the surface memory.
	SDL_FreeSurface(surface);
}

// This will change ALL of the TextRenderer's currently in the game
// Will adapt it later with probably a FontManager as well.
void TextRenderer::SetFontSize(unsigned int size) {
	if (_size == size) return;

	_size = size;
	SetText(_text, color);
}

// Cleanup Textures.
void TextRenderer::CollectGarbage() { if (tex) SDL_DestroyTexture(tex); }
TextRenderer::~TextRenderer() { CollectGarbage(); }