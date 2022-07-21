#include "RenderManager.h"
#include "EntityManager.h"

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
	EntityMgr.RenderAllEntities();
	SDL_RenderPresent(renderer);
}

void Renderer::LoadTexture(std::string path, SDL_Texture** output) {
	*output = IMG_LoadTexture(MainRenderer.renderer, path.c_str());
	if (*output == nullptr) GAME.Debug("Unable to load the texture! Path: " + path);
}

Renderer::~Renderer() {
	GAME.Debug("Quitting Game -- Destroy SDL");
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}