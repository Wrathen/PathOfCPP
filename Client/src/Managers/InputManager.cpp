#include "InputManager.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "Entities/Monster.h"

void InputManager::OnKeyDown(SDL_Keycode keyCode) {
    switch (keyCode) {
        case SDLK_ESCAPE:
            GAME.Quit();
            break;
        case SDLK_1:
            {
                // [To:Do]
                // You know we shouldn't load the same texture 10000 times, right?
                // Have some loaded textures stored or smthn
                for (int i = 0; i < 10000; ++i)
                    new Monster("assets/monster.png", "War boar");
            }
            EntityMgr.PrintAllEntities();
            break;
        case SDLK_2:
            GAME.Debug(EntityMgr.GetEntity(0)->ToString());
            break;
        case SDLK_3:
            GAME.Debug(EntityMgr.GetEntity(1)->ToString());
            break;
        case SDLK_4:
            EntityMgr.RemoveEntity(EntityMgr.GetEntity(0));
            break;
        case SDLK_5:
            EntityMgr.RemoveEntity(EntityMgr.GetEntity(1));
            break;
    }
}
void InputManager::OnKeyUp(SDL_Keycode keyCode) {
    switch (keyCode) {
        case SDLK_ESCAPE:
            GAME.Debug("heyo up");
            break;
        case SDLK_w:
            GAME.Debug("hi up");
            break;
    }
}