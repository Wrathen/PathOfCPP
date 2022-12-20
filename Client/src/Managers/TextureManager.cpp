#include "TextureManager.h"
#include "RenderManager.h"
#include "../Miscellaneous/Log.h"

// Static Functions
SDL_Point TextureManager::GetDimensions(SDL_Texture* tex) {
	SDL_Point size;
	SDL_QueryTexture(tex, NULL, NULL, &size.x, &size.y);
	return size;
}

// Main Functions
SDL_Texture* TextureManager::LoadTextureFromCache(std::string path) {
	auto entity = textureCache.find(path);
	return entity != textureCache.end() ? entity->second : nullptr;
}
void TextureManager::LoadTexture(std::string path, SDL_Texture** output) {
	auto cache = LoadTextureFromCache(path);
	if (cache) {
		//Debug("Loading " + path + " from cached textures.");

		*output = cache;
		return;
	}

	*output = IMG_LoadTexture(MainRenderer.renderer, path.c_str());
	textureCache[path] = *output;
	if (*output == nullptr) Warn("Unable to load the texture! Path: " + path);
}

TextureManager::~TextureManager() { for (auto& itr : textureCache) SDL_DestroyTexture(itr.second); }