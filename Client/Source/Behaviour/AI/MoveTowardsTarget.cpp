#include "MoveTowardsTarget.h"
#include "../../Managers/GameManager.h"
#include "../../Entities/Monster.h"
#include "../../Miscellaneous/Time.h"

void MoveTowardsTarget::Start() {
	sourceStats = source->GetComponent<Stats>();
	sourceTransform = &source->transform;
}
void MoveTowardsTarget::Update() {
	if (!isEnabled || !target) return;

	// If we are too far away, do not move towards the target.
	float distance = Vector2::DistanceBetween(sourceTransform->position, targetTransform->position);
	if (distance < 2.5f) {
		target->GetComponent<Health>()->TakeDamage(0.3f);
	}
	else if (distance > 1500.0f) return;

	// Calculate the direction and move towards the target.
	float angle = Vector2::AngleBetween(sourceTransform->position, targetTransform->position);
	Vector2 dir = Vector2::FromAngle(angle);

	sourceTransform->Move(dir, sourceStats->GetMoveSpeed());
}