#pragma once
#include "../../../Entities/Entity.h"

class BreachLeagueEncounter: Entity { 
public:
	friend class BreachLeague;
	enum EncounterState { Idle, Expanding, Shrinking, Ended };

	EncounterState currentState = Idle;
	float currentRadius = 1.0f;

	void StartEncounter();
	void EndEncounter();
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