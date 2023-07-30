#include "TextRenderer.h"
#include "../Managers/RenderManager.h"
#include "../Miscellaneous/Log.h"

// Constructor
TextRenderer::TextRenderer() {};

// Base Functions
void TextRenderer::Render() {
	// Draw the background first, then draw the usual text.
	if (_outlineSize > 0) outlineRenderer.Render();
	Super::Render();
}

// Main Functions
void TextRenderer::SetText(std::string text, SDL_Color color, bool forceSet) {
	if (!forceSet && text == _text) return;
	CollectGarbage();

	_text = text;
	_color = color;

	SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(MainRenderer.GetFont(_size), _text.c_str(), color, 0);
	Super::AssignTexture(SDL_CreateTextureFromSurface(MainRenderer.renderer, surface));

	SDL_FreeSurface(surface);

	SetOutlineText({ 255, 255, 255 }, 4);
}

// Draws outline text.
void TextRenderer::SetOutlineText(SDL_Color color, unsigned int outlineSize) {
	_outlineSize = outlineSize;
	_outlineColor = color;

	SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(MainRenderer.GetFont(_size + outlineSize), _text.c_str(), color, 0);
	outlineRenderer.AssignTexture(SDL_CreateTextureFromSurface(MainRenderer.renderer, surface));

	SDL_FreeSurface(surface);
}

// This will change ALL of the TextRenderer's currently in the game
// Will adapt it later with probably a FontManager as well.
void TextRenderer::SetFontSize(unsigned int size) {
	if (_size == size) return;

	_size = size;
	SetText(_text, _color);
}

// Cleanup Textures.
void TextRenderer::CollectGarbage() {
	if (tex) SDL_DestroyTexture(tex);
	if (outlineRenderer.tex) SDL_DestroyTexture(outlineRenderer.tex);
}