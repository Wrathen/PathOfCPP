#include "Scene_Forest.h"
#include "../Managers/EnemySpawnManager.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameManager.h"
#include "../UI/UserInterface.h"

Scene_Forest::Scene_Forest() : Scene("Zone_Forest.PZD") {};

void Scene_Forest::Start() { Super::Start(); }
void Scene_Forest::Update() { Super::Update(); 
	if (InputMgr.IsKeyPressed(SDLK_x))
		GAME.GetPlayer()->GainXP(2);
}
void Scene_Forest::LateUpdate() { }
void Scene_Forest::Clear() { Super::Clear(); }