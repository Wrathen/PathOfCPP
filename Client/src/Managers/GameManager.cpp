#include "GameManager.h"
#include "InputManager.h"
#include "../Entities/Entity.h"
#include "RenderManager.h"

// Base Functions
void GameManager::Init() {
    MainRenderer.Init();
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

        MainRenderer.Draw();
    }
}
void GameManager::Quit() {
    GAME.isGameRunning = false;
}

// Main Functions
void GameManager::Debug(std::string_view msg) {
    std::cout << msg << std::endl;
}