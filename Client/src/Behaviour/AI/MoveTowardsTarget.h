#pragma once
#include "../../Entities/Entity.h"
#include "../../Components/Stats.h"

class MoveTowardsTarget: public Component {
public:
	Entity* target = nullptr;
	Stats* sourceStats = nullptr;
	Transform* sourceTransform = nullptr;
	Transform* targetTransform = nullptr;

	bool isEnabled = true;

	// Base Functions
	void Start();
	void Update();

	// Main Functions
	void SetEnabled(bool flag) { isEnabled = flag; }
	void SetTarget(Entity* tar) { target = tar; targetTransform = &target->transform; }
	Entity* GetTarget() { return target; }
	void Delete() { delete this; }
};