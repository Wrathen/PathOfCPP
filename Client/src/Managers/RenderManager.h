#pragma once
#include <SDL_image.h>
#include <unordered_map>
#include "GameManager.h"
#include "../Components/BaseRenderer.h"
#include "../Miscellaneous/GUID.h"

#define MainRenderer Renderer::GetInstance()
class Renderer {
public:
    static Renderer& GetInstance() {
        static Renderer instance;
        return instance;
    }

    void Init();
    void Start();
    void Draw();

    void LoadTexture(std::string path, SDL_Texture** output);
    void AddRenderer(BaseRenderer* renderer);
    void RemoveRenderer(BaseRenderer* renderer);
    BaseRenderer* GetRenderer(GUID guid);

private:
    Renderer() {}
    ~Renderer();
    Renderer(Renderer const&) = delete;
    void operator=(Renderer const&) = delete;

public:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* gTexture = nullptr;

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

public:
    std::unordered_map<GUID, BaseRenderer*> rendererList;
};