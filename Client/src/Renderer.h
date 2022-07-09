#pragma once
#include <SDL_image.h>
#include "GameManager.h"

#define Render Renderer::GetInstance()
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

private:
    Renderer() {}
    ~Renderer() {
        GAME.Debug("Quitting Game -- Destroy SDL");
        SDL_DestroyTexture(gTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        IMG_Quit();
    }
    Renderer(Renderer const&) = delete;
    void operator=(Renderer const&) = delete;

public:
    SDL_Window* window;
    SDL_Renderer* renderer;

    SDL_Texture* gTexture = nullptr;

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
};