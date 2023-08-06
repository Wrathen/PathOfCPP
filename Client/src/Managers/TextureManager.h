#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include <string>
#include "../Miscellaneous/Singleton.h"

#define TextureMgr TextureManager::GetInstance()
class TextureManager : public Singleton<TextureManager> { friend class Singleton;
public:
	static SDL_Point GetDimensions(SDL_Texture* tex);
	void LoadTexture(std::string path, SDL_Texture** output);

private:
	std::unordered_map<std::string, SDL_Texture*> textureCache;
	SDL_Texture* LoadTextureFromCache(std::string path);

private:
	TextureManager() {}
	~TextureManager();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
};