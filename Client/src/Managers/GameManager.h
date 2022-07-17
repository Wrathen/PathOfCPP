#pragma once
#include <SDL.h>
#include <iostream>

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
    void Quit();

    // Main Functions
    void Debug(std::string_view msg);

private:
    GameManager() {}
    ~GameManager() {}
    GameManager(GameManager const&) = delete;
    void operator=(GameManager const&) = delete;

public:
    SDL_Event event;
    bool isGameRunning = true;
};