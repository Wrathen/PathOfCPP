#include "InputManager.h"
#include "GameManager.h"
#include "EntityManager.h"

void InputManager::OnKeyDown(SDL_Keycode keyCode) {
    switch (keyCode) {
        case SDLK_ESCAPE:
            GAME.Quit();
            break;
        case SDLK_1:
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