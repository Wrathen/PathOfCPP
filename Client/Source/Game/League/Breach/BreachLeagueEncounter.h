#pragma once
#include <vector>
#include "../../../Entities/Entity.h"
#include "../../../Entities/Monsters/BreachMonster.h"

class BreachLeagueEncounter: Entity { 
public:
	friend class BreachLeague;
	enum EncounterState { Idle, Expanding, Shrinking, Ended };
	
	EncounterState currentState = Idle;
	float maxExpandRadius = 4.0f;
	float currentRadius = 1.0f;

	// Spawn Behaviour
	std::vector<BreachMonster*> spawnedMonsters;
	uint32_t totalNumberOfSpawns = -1;
	int eachWaveSpawnCount = -1;

	void StartEncounter();
	void EndEncounter();
	void ClearAllSpawnedMonsters();
	void Expand();
	void Shrink();

	// CTor
	BreachLeagueEncounter();

	// Events
	void Start() override {};
	void Update() override;
	void OnKill() override {};
	void OnDeath() override {};
};