#include "Scene_Town.h"
#include "../Managers/EnemySpawnManager.h"
#include "../Game/Zone/Zone.h"
#include "../Managers/InputManager.h"
#include "../Managers/GameManager.h"

Scene_Town::Scene_Town() : Scene("Town") {}

void Scene_Town::Start() {
	Super::Start();

	Zone zone = Zone::FromSaveFile("C:\\Users\\frost\\Desktop\\CPP Journey\\PathOfCPP\\Client\\build\\Zone_Town.PZD");

	background.SetProperties(zone.GetBackground().bgPath, GAME.gameWidth, GAME.gameHeight); // assets/bg1.png
	//background.renderer.UpdateTextureDimensions();

	EnemySpawner.SetSpawnAmount(0);
	EnemySpawner.SetMaxSpawnAmount(0);
	EnemySpawner.SetSpawnInterval(1000000);

	for (const ZoneEntityData& entity : zone.GetEntities())
		EnemySpawner.SpawnNPC(entity.ID, entity.position.x - 1920/2, entity.position.y - 1080/2);
}
void Scene_Town::Update() {
	Super::Update();

	if (InputMgr.IsKeyPressed(SDLK_c))
		GAME.GetPlayer()->transform.SetPosition(0, 0);
}
void Scene_Town::LateUpdate() {}

void Scene_Town::Clear() { Scene::Clear(); }