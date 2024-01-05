#pragma once
#include "../Monster.h"
#include "Behaviour/Leagues/Breach/BreachMonsterAI.h"
#include <string>

class BreachMonster : public Monster {
public:
	BreachMonster();
	BreachMonster(std::string name);

	BreachMonsterAI* breachMonsterAI = nullptr;

	void OnDeath() override;

	~BreachMonster();
};