#include "TextureManager.h"
#include "RenderManager.h"
#include "../Miscellaneous/Log.h"

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