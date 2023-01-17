#pragma once
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Timer.h"
#include "../Entities/Monsters/Zombie.h"
#include "../Entities/Monsters/Boar.h"

#define EnemySpawner EnemySpawnManager::GetInstance()
class EnemySpawnManager: public Singleton<EnemySpawnManager> { friend class Singleton;
private:
	Timer timer;
	// Wave Spawn Interval in Milliseconds
	float spawnInterval = 333;
	// Number of enemies to spawn per wave
	int spawnAmount = 2;
	int maxSpawnAmount = 1000;

public:
	int totalNumberOfSpawnedEnemies = 0;
	int totalNumberOfSpawnedWaves = 0;

	float GetSpawnInterval() { return spawnInterval; }
	int GetSpawnAmount() { return spawnAmount; }
	void SetSpawnInterval(float interval);
	void SetSpawnAmount(int amount);
	void SpawnEnemy();

	void Start();
	void Update();

private:
	EnemySpawnManager() { Start(); }
	~EnemySpawnManager() {}
	EnemySpawnManager(EnemySpawnManager const&) = delete;
	void operator=(EnemySpawnManager const&) = delete;
};