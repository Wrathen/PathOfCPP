#include "ShootArrow.h"
#include "Entities/Entity.h"
#include "Miscellaneous/Mouse.h"
#include "Components/Stats.h"
#include "Entities/Projectile.h"

void ShootArrow::Start() {
	Shoot(Mouse::GetPosition());
	caster->CancelActiveAbility(this);
}
void ShootArrow::Update() {}
void ShootArrow::Delete() { delete this; }

void ShootArrow::Shoot(const Vector2& targetPos) {
	Stats* casterStats = caster->GetComponent<Stats>();
	if (!casterStats) {
		Error("Caster stats does not exist. Why do you even try to activate an ability with an incompatible entity?");
		return;
	}

	int numberOfProjectiles = casterStats->GetNumberOfProjectiles();
	float mainRotation = Vector2::AngleBetween(caster->transform.GetScreenPosition(), targetPos);

	// used to be 1.30895833f or PI/2.4 = ~75 degrees spread.
	float spreadDistance = (3.1415f * 2 * casterStats->GetProjectileSpread()) / numberOfProjectiles;
	bool isEven = numberOfProjectiles % 2 == 0;

	Projectile* lastInstantiatedProjectile = nullptr;
	static const float epsilon = 0.025f;
	float previousOffset = -999;

	for (int i = 0; i < numberOfProjectiles; ++i) {
		int multiplier = i - numberOfProjectiles / 2;
		if (isEven && multiplier >= 0) ++multiplier;

		float offset = spreadDistance * multiplier;
		float rotation = mainRotation + offset;

		// Do not instantiate close projectiles, instead give the previous one piercing.
		if (offset - epsilon < previousOffset && previousOffset < offset + epsilon) {
			if (lastInstantiatedProjectile)
				++lastInstantiatedProjectile->overlappingProjectiles;
			continue;
		}

		previousOffset = offset;
		lastInstantiatedProjectile = new Projectile(caster, caster->transform.GetPosition(), rotation, casterStats->GetProjectileSpeed());
	}
}