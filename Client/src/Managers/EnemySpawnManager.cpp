#include <cmath>
#include "EnemySpawnManager.h"
#include "../Managers/GameManager.h"
#include "../Behaviour/AI/MoveTowardsTarget.h"
#include "../Miscellaneous/Log.h"

void EnemySpawnManager::SetSpawnInterval(float interval) { spawnInterval = interval; }
void EnemySpawnManager::SetSpawnAmount(int amount) { spawnAmount = amount; }
void EnemySpawnManager::SpawnEnemy() {
	if (totalNumberOfSpawnedEnemies > 1000000) return;

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

	// Do some statistics :^)
	++totalNumberOfSpawnedEnemies;
}
void EnemySpawnManager::Update() {
	// Elapse the time between the last wave
	auto elapsedTime = timer.GetTimeMS();
	if (elapsedTime < spawnInterval) return;

	// Spawn a wave of enemies and reset the timer
	for (int i = 0; i < spawnAmount; ++i) SpawnEnemy();
	timer.Reset();

	// Do some statistics :^)
	++totalNumberOfSpawnedWaves;
}