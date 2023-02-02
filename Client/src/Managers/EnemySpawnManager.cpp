#include <cmath>
#include "EnemySpawnManager.h"
#include "../Managers/GameManager.h"
#include "../Behaviour/AI/MoveTowardsTarget.h"
#include "../Miscellaneous/Log.h"

#include "../Entities/NPCs/Blacksmith.h"
#include "../Entities/NPCs/Merchant.h"
#include "../Entities/NPCs/Gambler.h"

void EnemySpawnManager::SetSpawnInterval(float interval) { spawnInterval = interval; }
void EnemySpawnManager::SetSpawnAmount(int amount) { spawnAmount = amount; }
void EnemySpawnManager::SetMaxSpawnAmount(int amount) { maxSpawnAmount = amount; }

void EnemySpawnManager::SpawnEnemy() {
	if (totalNumberOfSpawnedEnemies >= maxSpawnAmount) return;

	auto random = RandomInt(0, 2);
	Monster* enemy = nullptr;

	// Create an Enemy with a random type
	if (random == 0) enemy = new Boar();
	else enemy = new Zombie();

	// Set the created enemy's position randomly in a circular way.
	float direction = RandomFloat(0.0f, 6.283f);
	float distance = RandomFloat(750.0f, 950.0f);
	Vector2 offset = GAME.GetPlayer()->transform.GetPosition();

	float x = cos(direction) * distance + offset.x;
	float y = sin(direction) * distance + offset.y;
	enemy->transform.SetPosition(x, y);
	enemy->CStats->SetLevel(monsterLevel);

	// Do some statistics :^)
	++totalNumberOfSpawnedEnemies;
}
void EnemySpawnManager::SpawnNPC(int type) {
	NPC* npc = nullptr;
	switch (type) {
		case 0:
			npc = new Merchant("Bilbo");
			break;
		case 1:
			npc = new Gambler("Zeus");
			break;
		default:
			npc = new Blacksmith("Patrick");
			break;
	}

	// Set the created enemy's position randomly in a circular way.
	float direction = RandomFloat(0.0f, 6.283f) * 25.0f;
	float distance = RandomFloat(150.0f, 350.0f);
	Vector2 offset = GAME.GetPlayer()->transform.GetPosition();

	float x = cos(direction) * distance + offset.x;
	float y = sin(direction) * distance + offset.y;
	npc->transform.SetPosition(x, y);
}

void EnemySpawnManager::SetMonsterLevel(int value) { monsterLevel = value; }

void EnemySpawnManager::Start() {}
void EnemySpawnManager::Update() {
	if (GAME.isGamePaused) return;

	// Elapse the time between the last wave
	auto elapsedTime = timer.GetTimeMS();
	if (elapsedTime < spawnInterval) return;

	// Spawn a wave of enemies and reset the timer
	for (int i = 0; i < spawnAmount; ++i) SpawnEnemy();
	timer.Reset();

	// Do some statistics :^)
	++totalNumberOfSpawnedWaves;
}