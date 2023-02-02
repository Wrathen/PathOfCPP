#include "Scene_Town.h"
#include "../Managers/EnemySpawnManager.h"

void Scene_Town::Start() {
	background.SetProperties("assets/bg1.png", 1920 * 64, 1080 * 64);

	EnemySpawner.SetSpawnAmount(0);
	EnemySpawner.SetMaxSpawnAmount(0);
	EnemySpawner.SetSpawnInterval(1000000);

	EnemySpawner.SpawnNPC(0);
	EnemySpawner.SpawnNPC(1);
	EnemySpawner.SpawnNPC(2);
}
void Scene_Town::Update() {
	static int playerLevel;

	// Render
	background.Render();
}
void Scene_Town::LateUpdate() {}

void Scene_Town::Clear() { Scene::Clear(); }