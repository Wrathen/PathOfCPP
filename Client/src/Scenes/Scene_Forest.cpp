#include "Scene_Forest.h"
#include "../Managers/EnemySpawnManager.h"

static int playerLevel;
void Scene_Forest::Start() {
	background.SetProperties("assets/BarkTexture-01.png", 1920 * 64, 1080 * 64);
	xpBar = new XPBar();

	EnemySpawner.SetSpawnAmount(2);
	EnemySpawner.SetMaxSpawnAmount(10000);
	EnemySpawner.SetSpawnInterval(333);
}
void Scene_Forest::Update() {
	EnemySpawner.Update();

	// Update XP Bar
	Player* p = GAME.GetPlayer();
	xpBar->SetXP(p->stats->GetXP());
	xpBar->SetMaxXP(p->stats->GetMaxXP());
	if (playerLevel != p->stats->GetLevel()) {
		playerLevel = p->stats->GetLevel();
		xpBar->SetLevel(p->stats->GetLevel());
	}

	// Render
	background.Render();
}
void Scene_Forest::LateUpdate() { }

void Scene_Forest::Clear() {
	playerLevel = 0;
	xpBar->Delete();
	Scene::Clear();
}