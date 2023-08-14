#pragma once
#include "BreachLeagueEncounter.h"

class BreachLeague {
public:
	BreachLeagueEncounter* encounter = nullptr;
	
	// Main Functions
	void Init();
	void Update();

	void CreateNewBreach();
};