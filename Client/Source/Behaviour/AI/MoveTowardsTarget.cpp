#include "MoveTowardsTarget.h"
#include "Managers/GameManager.h"
#include "Entities/Monster.h"
#include "Miscellaneous/Time.h"

void MoveTowardsTarget::Start() {
	sourceStats = source->GetComponent<Stats>();
	sourceTransform = &source->transform;
}
void MoveTowardsTarget::Update() {
	if (!isEnabled || !target) return;

	// If we are too far away, do not move towards the target.
	float distance = Vector2::DistanceBetween(sourceTransform->GetPosition(), targetTransform->GetPosition());
	if (distance < 2.5f) {
		target->GetComponent<Health>()->TakeDamage(0.3f);
	}
	else if (distance > 1500.0f) return;

	// Calculate the direction and move towards the target.
	float angle = Vector2::AngleBetween(sourceTransform->GetPosition(), targetTransform->GetPosition());
	sourceTransform->SetVelocity(Vector2::FromAngle(angle) * sourceStats->GetMoveSpeed());

	Vector2 velocityNormalized = sourceTransform->GetVelocity();
	velocityNormalized = velocityNormalized.Normalize();

	// Check if the target position is movable.
	Vector2 nextFramePosition = sourceTransform->GetPositionNextFrame(velocityNormalized, sourceStats->GetMoveSpeed());

	// Set new position.
	sourceTransform->SetPosition(nextFramePosition);
}