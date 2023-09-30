#include "Dash.h"
#include "Entities/Entity.h"
#include "Miscellaneous/Mouse.h"

void Dash::Start() {
	auto dashDirection = (Mouse::GetPosition() - caster->transform.GetScreenPosition()).Normalize();

	casterStats = caster->GetComponent<Stats>();
	casterStats->AddMoveSpeedMultiplier(3.0f);

	caster->transform.SetVelocity(dashDirection);
	caster->transform.LockVelocity(true);
}
void Dash::Update() {
	if (lifetimeTimer.GetTimeMS() > 300) {
		caster->CancelActiveAbility(this);
		return;
	}
}
void Dash::Delete() {
	caster->transform.LockVelocity(false);
	casterStats->AddMoveSpeedMultiplier(-3.0f); 
	delete this; 
}