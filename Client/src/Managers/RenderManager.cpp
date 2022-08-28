#include "RenderManager.h"
#include "EntityManager.h"
#include "UIManager.h"
#include "../Miscellaneous/Log.h"

void Renderer::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("Path of CPP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	Start();
}
void Renderer::Start() {}
void Renderer::Draw() {
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	EntityMgr.RenderAllEntities();
	UIMgr.RenderAllElements();

	SDL_RenderPresent(renderer);
}

Renderer::~Renderer() {
	Debug("Quitting Game -- Destroy SDL");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}