#include "TextureManager.h"
#include "RenderManager.h"
#include "../Miscellaneous/Log.h"

// Static Functions
SDL_Point TextureManager::GetDimensions(GPU_Image* img) { return { img->w, img->h }; }

// Main Functions
GPU_Image* TextureManager::LoadTextureFromCache(std::string path) {
	auto entity = textureCache.find(path);
	return entity != textureCache.end() ? entity->second : nullptr;
}
void TextureManager::LoadTexture(std::string path, GPU_Image** output) {
	auto cache = LoadTextureFromCache(path);
	if (cache) {
		//Debug("Loading " + path + " from cached textures.");

		*output = cache;
		return;
	}

	*output = GPU_LoadImage(path.c_str());
	textureCache[path] = *output;
	if (*output == nullptr) Warn("Unable to load the texture! Path: " + path);
}

TextureManager::~TextureManager() { for (auto& itr : textureCache) GPU_FreeImage(itr.second); }