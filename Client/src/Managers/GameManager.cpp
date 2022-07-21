#include "GameManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "../Entities/Entity.h"
#include "../Entities/Monster.h"

// Base Functions
void GameManager::Init() {
    MainRenderer.Init();
    Start();
}
void GameManager::Start() {
    Entity* player = new Entity("Wrathen");
    Entity* someEnemy = new Entity("Rat");
    Monster* veryDangerousMonster = new Monster("Sirus");
    Monster* finallyAVisibleMonster = new Monster("assets/monster.png", "Cortex");

    GAME.Debug(player->ToString());
    GAME.Debug(someEnemy->ToString());
    GAME.Debug(veryDangerousMonster->ToString());
    GAME.Debug(finallyAVisibleMonster->ToString());

    Update();
}
void GameManager::Update() {
    while (GAME.isGameRunning) {
        PollEvents();
        EntityMgr.UpdateAllEntities();
        MainRenderer.Draw();
    }
}
void GameManager::PollEvents() {
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
}
void GameManager::Quit() { GAME.isGameRunning = false; }

// Main Functions
void GameManager::Debug(std::string_view msg) {
    std::cout << msg << std::endl;
}