#pragma once
#include <unordered_map>
#include <SDL_gpu.h>
#include <string>
#include "../Miscellaneous/Singleton.h"

#define TextureMgr TextureManager::GetInstance()
class TextureManager : public Singleton<TextureManager> { friend class Singleton;
public:
	static SDL_Point GetDimensions(GPU_Image* tex);
	void LoadTexture(std::string path, GPU_Image** output);

private:
	std::unordered_map<std::string, GPU_Image*> textureCache;
	GPU_Image* LoadTextureFromCache(std::string path);

private:
	TextureManager() {}
	~TextureManager();
	TextureManager(TextureManager const&) = delete;
	void operator=(TextureManager const&) = delete;
};