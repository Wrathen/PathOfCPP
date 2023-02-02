#include "Scene_Forest.h"
#include "../Managers/EnemySpawnManager.h"
#include "../UI/UserInterface.h"

void Scene_Forest::Start() {
	timer = Timer();
	background.SetProperties("assets/bg3.jpg", 1920 * 64, 1080 * 64);
	
	EnemySpawner.SetMonsterLevel(1);
	EnemySpawner.SetSpawnAmount(3);
	EnemySpawner.SetMaxSpawnAmount(40000000);
	EnemySpawner.SetSpawnInterval(480);
	EnemySpawner.Reset();
}
void Scene_Forest::Update() {
	EnemySpawner.Update();

	if (timer.GetTimeMS() > 9000) {
		EnemySpawner.SetMonsterLevel(GAME.GetPlayer()->CStats->GetLevel());
		EnemySpawner.SetSpawnAmount(EnemySpawner.GetSpawnAmount() + 1);
		timer.Reset();
	}

	// Render
	background.Render();
}
void Scene_Forest::LateUpdate() { }

void Scene_Forest::Clear() { Scene::Clear(); }