#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include <string>

#define TextureMgr TextureManager::GetInstance()
class TextureManager {
public: // Methods
	static TextureManager& GetInstance() {
		static TextureManager instance;
		return instance;
	}
	void LoadTexture(std::string path, SDL_Texture** output);

private: // Methods
	SDL_Texture* LoadTextureFromCache(std::string path);

public: // Members
	std::unordered_map<std::string, SDL_Texture*> textureCache;
};