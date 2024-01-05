#pragma once
#include "../../../Entities/Monsters/BreachMonster.h"

class BreachLeagueEncounter: public Entity { 
public:
	friend class BreachLeague;
	enum EncounterState { Idle, Expanding, Shrinking, Ended };
	
	EncounterState currentState = Idle;
	float maxExpandRadius = 4.0f;
	float currentRadius = 1.0f;

	// Spawn Behaviour
	std::vector<std::shared_ptr<BreachMonster>> allMonsters;
	uint32_t totalNumberOfSpawns = -1;
	int eachWaveSpawnCount = -1;

	void StartEncounter();
	void EndEncounter();
	void ClearAllSpawnedMonsters();
	void Expand();
	void Shrink();

	void OnOutOfRange(BreachMonster* monster);
	void CreateBreachMonster(float posX, float posY);
	void DeleteBreachMonster(BreachMonster* monster);

	void OnExpandTick();
	void OnShrinkTick();

	// Utilities
	float GetRadius();

	// CTor
	BreachLeagueEncounter();

	// Events
	void Start() override {};
	void Update() override;
	void OnKill() override {};
	void OnDeath() override {};
};