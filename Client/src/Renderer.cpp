#include "Renderer.h"

void Renderer::Init() {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    window = SDL_CreateWindow("Path of CPP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    LoadTexture("assets/2.png", &gTexture);
    Start();
}
void Renderer::Start() { }
void Renderer::Draw() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, gTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Renderer::LoadTexture(std::string path, SDL_Texture** output) {
    *output =  IMG_LoadTexture(renderer, path.c_str());
    if (*output == nullptr) GAME.Debug("Unable to load the texture! Path: " + path);
}