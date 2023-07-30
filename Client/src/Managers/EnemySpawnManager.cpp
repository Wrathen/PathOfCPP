#include <cmath>
#include "EnemySpawnManager.h"
#include "../Managers/GameManager.h"
#include "../Behaviour/AI/MoveTowardsTarget.h"
#include "../Miscellaneous/Log.h"
#include "../Entities/NPCs/Blacksmith.h"
#include "../Entities/NPCs/Merchant.h"
#include "../Entities/NPCs/Gambler.h"

// Main Functions
void EnemySpawnManager::AddNPCs(const std::vector<ZoneEntityData>& entityData) {
	entities = entityData;

	for (const ZoneEntityData& npc : entities)
		SpawnNPC(npc.ID, npc.position.x - 2000, npc.position.y - 2000);
}
void EnemySpawnManager::AddSpawnZones(const std::vector<ZoneSpawnZoneData>& spawnZoneData) {
	spawnZones = spawnZoneData;
	// @todo this should be a stat of zones. think like map multipliers.
	uint32_t monsterMultiplier = 2;

	for (const ZoneSpawnZoneData& spawnZone : spawnZones)
		for (uint32_t i = 0; i < spawnZone.amount * monsterMultiplier; ++i)
			SpawnMonsterInZone(spawnZone);
}

void EnemySpawnManager::SpawnNPC(int type, float x, float y) {
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

	npc->transform.SetPosition(x, y);

	// Do some statistics :^)
	++totalNumberOfSpawnedNPCs;
}
void EnemySpawnManager::SpawnMonster(float x, float y) {
	auto random = RandomInt(0, 2);
	Monster* enemy = nullptr;

	// Create an Enemy with a random type
	if (random == 0) enemy = new Boar();
	else enemy = new Zombie();

	// Set the stats of the newly created enemy.
	enemy->transform.SetPosition(x, y);
	enemy->CStats->SetLevel(monsterLevel);

	// Do some statistics :^)
	++totalNumberOfSpawnedMonsters;
}
void EnemySpawnManager::SpawnMonsterInZone(const ZoneSpawnZoneData& zone) {
	auto randomOffset = RandomVector(zone.w, zone.h);
	SpawnMonster(zone.position.x + randomOffset.x - 2000,
				 zone.position.y + randomOffset.y - 2000);
}