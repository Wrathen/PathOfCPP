#include "MoveTowardsTarget.h"
#include "../../Managers/GameManager.h"

void MoveTowardsTarget::Update() {
	if (!isEnabled || !target) return;

	// If we are too far away, do not move towards the target.
	float distance = Vector2::DistanceBetween(sourceTransform->position, targetTransform->position);
	if (distance > 500.0f) return;

	// Calculate the direction and move towards the target.
	float angle = Vector2::AngleBetween(sourceTransform->position, targetTransform->position);
	Vector2 dir = Vector2::FromAngle(angle);
	sourceTransform->Move(dir, source->GetStats()->moveSpeed);
}