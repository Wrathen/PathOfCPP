#include "Scene_Forest.h"
#include "../Managers/EnemySpawnManager.h"
#include "../UI/UserInterface.h"

void Scene_Forest::Start() {
	timer = Timer();
	background.SetProperties("assets/BarkTexture-01.png", 1920 * 64, 1080 * 64);
	
	EnemySpawner.SetMonsterLevel(1);
	EnemySpawner.SetSpawnAmount(7);
	EnemySpawner.SetMaxSpawnAmount(60000);
	EnemySpawner.SetSpawnInterval(333);
	EnemySpawner.Reset();
}
void Scene_Forest::Update() {
	EnemySpawner.Update();

	if (timer.GetTimeMS() > 1500) {
		EnemySpawner.SetMonsterLevel(EnemySpawner.GetMonsterLevel() + 1);
		timer.Reset();
	}

	// Render
	background.Render();
}
void Scene_Forest::LateUpdate() { }

void Scene_Forest::Clear() { Scene::Clear(); }