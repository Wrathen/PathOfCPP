#include "RenderManager.h"

/*void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_entity.getPos().x + (p_entity.getCurrentFrame().w - p_entity.getCurrentFrame().w*p_entity.getScale().x)/2;
	dst.y = p_entity.getPos().y + (p_entity.getCurrentFrame().h - p_entity.getCurrentFrame().h*p_entity.getScale().y)/2;
	dst.w = p_entity.getCurrentFrame().w*p_entity.getScale().x;
	dst.h = p_entity.getCurrentFrame().h*p_entity.getScale().y;

	SDL_RenderCopyEx(renderer, p_entity.getTex(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
}

void RenderWindow::render(int x, int y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}*/

void Renderer::Init() {
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);

	window = SDL_CreateWindow("Path of CPP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	LoadTexture("assets/2.png", &gTexture);
	Start();
}
void Renderer::Start() {}
void Renderer::Draw() {
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, gTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Renderer::LoadTexture(std::string path, SDL_Texture** output) {
	*output = IMG_LoadTexture(renderer, path.c_str());
	if (*output == nullptr) GAME.Debug("Unable to load the texture! Path: " + path);
}

void Renderer::AddRenderer(BaseRenderer* renderer) {
	if (renderer == nullptr) return;

	static GUID guid;
	renderer->AssignGUID(guid);
	rendererList[guid++] = renderer;
}
void Renderer::RemoveRenderer(BaseRenderer* renderer) {
	if (renderer == nullptr) return;

	GAME.Debug("Deleting " + renderer->ToString());
	GAME.Debug("Deleted " + std::to_string(rendererList.erase(renderer->guid)) + " entities.");
	delete renderer;
}
BaseRenderer* Renderer::GetRenderer(GUID guid) {
	auto entity = rendererList.find(guid);
	return entity != rendererList.end() ? entity->second : nullptr;
}
Renderer::~Renderer() {
	GAME.Debug("Quitting Game -- Destroy SDL");
	SDL_DestroyTexture(gTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
	
	for (auto& renderer : rendererList) delete renderer.second;
	rendererList.clear();
}