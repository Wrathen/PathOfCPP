#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_gpu.h>
#include <unordered_map>

#define MainRenderer Renderer::GetInstance()
class Renderer {
public:
    static Renderer& GetInstance() { static Renderer _i; return _i; }

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    std::unordered_map<int, TTF_Font*> fontMap;
    const char* fontPath = "Assets/Fonts/Friz Quadrata Regular.ttf"; // CHERL___

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    void Init();
    void Clear();
    void Draw();
    TTF_Font* GetFont(int size);

private:
    Renderer() {}
    ~Renderer();
    Renderer(Renderer const&) = delete;
    void operator=(Renderer const&) = delete;
};