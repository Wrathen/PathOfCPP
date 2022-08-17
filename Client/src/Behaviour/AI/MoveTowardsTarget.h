#pragma once
#include "../../Entities/Entity.h"

class MoveTowardsTarget
{
public:
	// Base Functions
	void Update();

	// Main Functions
	void SetEnabled(bool flag) { isEnabled = flag; }
	void SetSource(Entity* src) { source = src; sourceTransform = &src->transform; }
	void SetTarget(Entity* tar) { target = tar; targetTransform = &target->transform; }
	Entity* GetTarget() { return target; }

	bool isEnabled = true;
	Entity* source;
	Entity* target;

	Transform* sourceTransform;
	Transform* targetTransform;
};