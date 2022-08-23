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
	void LoadTexture(std::string path, SDL_Texture** output);

private:
	~TextureManager() { for (auto& itr : textureCache) SDL_DestroyTexture(itr.second); }
	SDL_Texture* LoadTextureFromCache(std::string path);

	std::unordered_map<std::string, SDL_Texture*> textureCache;
};