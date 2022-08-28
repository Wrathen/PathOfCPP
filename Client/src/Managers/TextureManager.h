#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include <string>

#define TextureMgr TextureManager::GetInstance()
class TextureManager {
public:
	static TextureManager& GetInstance() {
		static TextureManager instance;
		return instance;
	}
	static SDL_Point GetDimensions(SDL_Texture* tex) {
		SDL_Point size;
		SDL_QueryTexture(tex, NULL, NULL, &size.x, &size.y);
		return size;
	}

	void LoadTexture(std::string path, SDL_Texture** output);

private:
	~TextureManager() { for (auto& itr : textureCache) SDL_DestroyTexture(itr.second); }
	SDL_Texture* LoadTextureFromCache(std::string path);

	std::unordered_map<std::string, SDL_Texture*> textureCache;
};