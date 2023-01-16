#include "Player.h"
#include "Projectile.h"
#include "Monsters/Boar.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Mouse.h"

Player::Player(std::string name) : Entity("assets/sprites/player.png", name) { Start(); }

void Player::Start() {
	stats = AddComponent<Stats>();
	stats->SetMoveSpeed(25.0f);

	stats->SetProjectileSpeed(60);
	stats->SetNumberOfProjectiles(1);
	stats->SetAttackSpeed(0.3f);

	healthBar = AddComponent<HealthBar>();
	healthBar->transform.SetScale(3.5f, 3.0f);
	
	transform.SetScale(2.2f, 2.2f);

	collisionTag = EntityCollisionTag::Friendly;
}

void Player::Update() {
	transform.Move(transform.velocity.Normalize(), stats->GetMoveSpeed());

	if (stats->GetAttackingState() && attackTimer.GetTimeMS() > (stats->GetAttackSpeed() * 1000)) {
		ShootArrow(Mouse::GetPosition());
		attackTimer.Reset();
	}
}

void Player::ShootArrow(const Vector2& targetPos) {
	int numberOfProjectiles = stats->GetNumberOfProjectiles();
	float mainRotation = Vector2::AngleBetween(transform.GetScreenPosition(), targetPos);

	// used to be 1.30895833f or PI/2.4 = ~75 degrees spread.
	float spreadDistance = (3.1415f * stats->GetProjectileAngleMultiplier()) / numberOfProjectiles;
	bool isEven = numberOfProjectiles % 2 == 0;

	for (int i = 0; i < numberOfProjectiles; ++i) {
		int multiplier = i - numberOfProjectiles/2;
		if (isEven && multiplier >= 0) ++multiplier;

		float offset = spreadDistance * multiplier;
		float rotation = mainRotation + offset;
		
		new Projectile(this, transform.GetPosition(), rotation, stats->GetProjectileSpeed());
	}
}

void Player::OnDeath() {
	Warn("Implement Player::OnDeath.");
}
void Player::OnKill() {
	++stats->totalKills;
	FUN_Headhunter();
}

// HH nerfs in this patch. Sadge
// Let's have a headhunter in Path of CPP cuz I can't afford it in league LMAO
void Player::FUN_Headhunter() {
	int hhChance = 25;
	bool shouldStealBuff = RandomInt(100) < hhChance;
	if (!shouldStealBuff) return;

	int rnd = RandomInt(6);
	switch (rnd) {
	case 0:
		if (stats->GetSizeMultiplier() > 4.0f) return;
		stats->SetSizeMultiplier(stats->GetSizeMultiplier() * 1.05f);
		transform.SetScaleModifier(stats->GetSizeMultiplier());
		break;
	case 1:
		if (stats->GetMoveSpeed() > 100) return;
		stats->SetMoveSpeed(stats->GetMoveSpeed() * 1.05f);
		break;
	case 2:
		if (stats->GetProjectileSpeed() > 160) return;
		stats->SetProjectileSpeed(stats->GetProjectileSpeed() * 1.05f);
		break;
	case 3:
		if (stats->GetAttackSpeed() < 0.0001f) return;
		stats->SetAttackSpeed(stats->GetAttackSpeed() * 0.95f);
		break;
	case 4:
		stats->SetMaxHealth(stats->GetMaxHealth() * 1.25f);
		stats->SetHealth(stats->GetHealth() * 1.25f);
		break;
	case 5:
		if (stats->GetNumberOfProjectiles() > 1000) return;
		stats->SetNumberOfProjectiles(stats->GetNumberOfProjectiles() + 1);
		break;
	}
}