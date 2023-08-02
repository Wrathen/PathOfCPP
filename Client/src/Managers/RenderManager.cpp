#include "RenderManager.h"
#include "EntityManager.h"
#include "UIManager.h"
#include "../Miscellaneous/Log.h"

void Renderer::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();

	window = SDL_CreateWindow("Path of CPP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	//GPU_InitRenderer(GPU_RENDERER_OPENGL_4, 800, 600, GPU_DEFAULT_INIT_FLAGS);

	Start();
}
void Renderer::Start() {}
void Renderer::Clear() { SDL_RenderClear(renderer); }
void Renderer::Draw() {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 30);
	SDL_RenderPresent(renderer);
}

TTF_Font* Renderer::GetFont(int size) {
	if (fontMap.count(size) == 0)
		fontMap[size] = TTF_OpenFont(fontPath, size);

	return fontMap[size];
}

Renderer::~Renderer() {
	Debug("Quitting Game -- Destroy SDL");

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	for (auto& fontPair: fontMap)
		TTF_CloseFont(fontPair.second);

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}