#include "RenderManager.h"
#include "EntityManager.h"
#include "UIManager.h"
#include "../Miscellaneous/Log.h"

void Renderer::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	target = GPU_InitRenderer(GPU_RENDERER_OPENGL_4, 1920, 1080, GPU_DEFAULT_INIT_FLAGS);
	
	Start();
}
void Renderer::Start() {}
void Renderer::Clear() { GPU_Clear(target); }
void Renderer::Draw() { GPU_Flip(target); }

TTF_Font* Renderer::GetFont(int size) {
	if (fontMap.count(size) == 0)
		fontMap[size] = TTF_OpenFont(fontPath, size);

	return fontMap[size];
}

Renderer::~Renderer() {
	Debug("Quitting Game -- Destroy SDL");

	GPU_FreeTarget(target);
	for (auto& fontPair: fontMap)
		TTF_CloseFont(fontPair.second);

	SDL_Quit();
	TTF_Quit();
	GPU_Quit();
}