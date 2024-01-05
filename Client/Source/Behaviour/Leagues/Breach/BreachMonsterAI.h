#pragma once

#include <memory>
#include "Entities/Entity.h"

class BreachMonsterAI {
public:
	Entity* parentBreach = nullptr;
	Entity* parentMonster = nullptr;
	bool isShrinking = false;

	void OnShrinkTick(float breachRadius);
};