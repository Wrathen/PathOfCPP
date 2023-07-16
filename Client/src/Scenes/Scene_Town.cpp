#include "Scene_Town.h"
#include "../Managers/GameManager.h"
#include "../Managers/InputManager.h"

Scene_Town::Scene_Town(): Scene("Zone_Town.PZD") {}

void Scene_Town::Start() { Super::Start(); }
void Scene_Town::Update() {
	Super::Update();

	// #TODO remove -- Cheat code - Press C to teleport to <0, 0>.
	if (InputMgr.IsKeyPressed(SDLK_c))
		GAME.GetPlayer()->transform.SetPosition(0, 0);
}
void Scene_Town::LateUpdate() {}
void Scene_Town::Clear() { Super::Clear(); }