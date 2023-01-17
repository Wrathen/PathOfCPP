#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <unordered_map>
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/GUID.h"
#include "../Components/SpriteRenderer.h"

#define MainRenderer Renderer::GetInstance()
class Renderer : public Singleton<Renderer> { friend class Singleton;
public:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;

    void Init();
    void Start();
    void Clear();
    void Draw();

private:
    Renderer() {}
    ~Renderer();
    Renderer(Renderer const&) = delete;
    void operator=(Renderer const&) = delete;
};