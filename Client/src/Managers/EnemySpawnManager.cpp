#include "EnemySpawnManager.h"

void EnemySpawnManager::SetSpawnInterval(float interval) { spawnInterval = interval; }
void EnemySpawnManager::SetSpawnAmount(int amount) { spawnAmount = amount; }
void EnemySpawnManager::SpawnEnemy() {
	auto random = RandomInt(0, 2);

	if (random == 0) new Boar();
	else new Zombie();

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