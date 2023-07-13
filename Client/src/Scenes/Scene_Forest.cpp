#include "Scene_Forest.h"
#include "../Managers/EnemySpawnManager.h"
#include "../UI/UserInterface.h"

Scene_Forest::Scene_Forest() : Scene("Zone_Forest.PZD") {};

void Scene_Forest::Start() {
	Super::Start();
	timer = Timer();
}
void Scene_Forest::Update() {
	Super::Update();

	EnemySpawner.Update();

	if (timer.GetTimeMS() > 9000) {
		EnemySpawner.SetMonsterLevel(GAME.GetPlayer()->CStats->GetLevel());
		EnemySpawner.SetSpawnAmount(EnemySpawner.GetSpawnAmount() + 1);
		timer.Reset();
	}
}
void Scene_Forest::LateUpdate() { }
void Scene_Forest::Clear() { Super::Clear(); }