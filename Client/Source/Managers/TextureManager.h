#pragma once
#include <unordered_map>
#include <SDL_image.h>
#include <string>

#define TextureMgr TextureManager::GetInstance()
class TextureManager {
public:
	static TextureManager& GetInstance() { static TextureManager _i; return _i; }
	
	// Main Functions
	void LoadTexture(std::string path, SDL_Texture** output);
	static SDL_Point GetDimensions(SDL_Texture* tex);

private:
	std::unordered_map<std::string, SDL_Texture*> textureCache;
	SDL_Texture* LoadTextureFromCache(std::string path);

	TextureManager() {}
	~TextureManager();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
};