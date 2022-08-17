#include "MoveTowardsTarget.h"
#include "../../Managers/GameManager.h"

void MoveTowardsTarget::Update() {
	if (!isEnabled || !target) return;

	float angle = Vector2::AngleBetween(sourceTransform->position, targetTransform->position);
	Vector2 dir = Vector2::FromAngle(angle);
	sourceTransform->Move(dir, source->GetStats()->moveSpeed);
}