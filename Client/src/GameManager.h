#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include "InputManager.h"

#define GAME GameManager::GetInstance()
class GameManager {
public:
    static GameManager& GetInstance() {
        static GameManager instance;
        return instance;
    }

    // Base Functions
    void Init();
    void Start();
    void Update();
    void Draw();
    void Quit();

    // Main Functions
    void Debug(std::string_view msg);

private:
    GameManager() {};
    ~GameManager() {
        Debug("Quitting Game -- Destroy SDL");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    GameManager(GameManager const&) = delete;
    void operator=(GameManager const&) = delete;

public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    bool isGameRunning = true;
};