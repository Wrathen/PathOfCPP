#include "Scene_Town.h"
#include "../Managers/EnemySpawnManager.h"
#include "../Game/Zone/Zone.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameManager.h"

Scene_Town::Scene_Town() : Scene("Town") {}

void Scene_Town::Start() {
	Super::Start();

	Zone zone = Zone::FromSaveFile("C:\\Users\\frost\\Desktop\\CPP Journey\\PathOfCPP\\Client\\build\\ZoneTown.json");

	background.SetProperties(zone.GetBackground().bgPath, 1920 * 1, 1080 * 1); // assets/bg1.png

	EnemySpawner.SetSpawnAmount(0);
	EnemySpawner.SetMaxSpawnAmount(0);
	EnemySpawner.SetSpawnInterval(1000000);

	for (const ZoneEntityData& entity : zone.GetEntities())
		EnemySpawner.SpawnNPC(entity.ID);
}
void Scene_Town::Update() {
	Super::Update();

	if (InputMgr.IsKeyPressed(SDLK_c))
		GAME.GetPlayer()->transform.SetPosition(0, 0);
}
void Scene_Town::LateUpdate() {}

void Scene_Town::Clear() { Scene::Clear(); }