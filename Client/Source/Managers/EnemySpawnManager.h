#pragma once
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Timer.h"
#include "../Entities/Monsters/Zombie.h"
#include "../Entities/Monsters/Boar.h"
#include "../Game/Zone/Zone.h"

#define EnemySpawner EnemySpawnManager::GetInstance()
class EnemySpawnManager: public Singleton<EnemySpawnManager> {
	friend class Singleton;
private:
	std::vector<ZoneEntityData> entities;
	std::vector<ZoneSpawnZoneData> spawnZones;
	int monsterLevel = 1;

public:
	int totalNumberOfSpawnedNPCs = 0;
	int totalNumberOfSpawnedMonsters = 0;

	// Main Functions
	void SpawnNPC(int type, float x, float y);
	void SpawnMonster(float x, float y);
	void SpawnMonsterInZone(const ZoneSpawnZoneData& zone);

	void AddNPCs(const std::vector<ZoneEntityData>& entityData);
	void AddSpawnZones(const std::vector<ZoneSpawnZoneData>& spawnZoneData);
	void Reset() { monsterLevel = 1; totalNumberOfSpawnedNPCs = 0; totalNumberOfSpawnedMonsters = 0; }

	// Getters && Setters
	int GetMonsterLevel() { return monsterLevel; }
	void SetMonsterLevel(int value) { monsterLevel = value; }

private:
	EnemySpawnManager() {}
	~EnemySpawnManager() {}
	EnemySpawnManager(EnemySpawnManager const&) = delete;
	void operator=(EnemySpawnManager const&) = delete;
};