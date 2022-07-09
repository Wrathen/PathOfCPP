#include "GameManager.h"
#include "Entity.h"

// Base Functions
void GameManager::Init() {
    SDL_Init(SDL_INIT_EVERYTHING);

    GAME.window = SDL_CreateWindow("Path of CPP", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    GAME.renderer = SDL_CreateRenderer(window, -1, 0);
    Start();
}
void GameManager::Start() {
    Entity* player = new Entity("Wrathen");
    Entity* someEnemy = new Entity("Rat");

    GAME.Debug(player->ToString());
    GAME.Debug(someEnemy->ToString());

    Update();
}
void GameManager::Update() {
    while (GAME.isGameRunning) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    GAME.Quit();
                    break;
                case SDL_KEYDOWN:
                    InputMgr.OnKeyDown(event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    InputMgr.OnKeyUp(event.key.keysym.sym);
                    break;
            }
        }

        Draw();
    }
}
void GameManager::Draw() {
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    SDL_RenderPresent(renderer);
}
void GameManager::Quit() {
    GAME.isGameRunning = false;
}

// Main Functions
void GameManager::Debug(std::string_view msg) {
    std::cout << msg << std::endl;
}