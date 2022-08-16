#include "InputManager.h"
#include "GameManager.h"
#include "EntityManager.h"
#include "../Entities/Monster.h"

void InputManager::OnKeyDown(SDL_Keycode keyCode) {
    switch (keyCode) {
        case SDLK_ESCAPE:
            GAME.Quit();
            break;
        case SDLK_1:
            for (int i = 0; i < 10; ++i) new Monster("assets/monster.png", "War boar");
            EntityMgr.PrintAllEntities();
            break;
        case SDLK_2:
            GAME.Debug(EntityMgr.GetEntity(0)->ToString());
            break;
        case SDLK_3:
            GAME.Debug(EntityMgr.GetEntity(1)->ToString());
            break;
        case SDLK_4:
            // [TO-DO] So, when you destroy Entity with GUID 0, which is the player
            // Our player pointer in the GameManager doesn't get nullified (set to nullptr).
            // I currently don't know if there's a general rule to fix this (maybe smart pointers or smthn?)
            // I can set it to nullptr manually, but I'll see if I will ever need to delete player pointer.
            // By then, leave it as is.
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