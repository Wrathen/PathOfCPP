#include "TextRenderer.h"
#include "../Managers/RenderManager.h"
#include "../Miscellaneous/Log.h"

void TextRenderer::CollectGarbage() { if (tex != nullptr) SDL_DestroyTexture(tex); }
TextRenderer::~TextRenderer() { CollectGarbage(); }

void TextRenderer::SetText(std::string text, SDL_Color color) {
	CollectGarbage();

	_text = text;
	_color = color;
	SDL_Surface* surface = TTF_RenderText_Solid_Wrapped(MainRenderer.GetFont(_size), _text.c_str(), color, 0);
	SpriteRenderer::AssignTexture(SDL_CreateTextureFromSurface(MainRenderer.renderer, surface));

	SDL_FreeSurface(surface);
}

// This will change ALL of the TextRenderer's currently in the game
// Will adapt it later with probably a FontManager as well.
void TextRenderer::SetFontSize(unsigned int size) {
	if (_size == size) return;

	_size = size;
	SetText(_text, _color);
}