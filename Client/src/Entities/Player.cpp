#include "Player.h"
#include "Projectile.h"
#include "../Miscellaneous/Log.h"

Player::Player(std::string name) : Entity("assets/sprites/player.png", name) { Start(); }

void Player::Start() {
	SetMoveSpeed(25.0f);

	SetProjectileSpeed(60);
	SetNumberOfProjectiles(1);
	SetAttackSpeed(0.09f);

	healthBar = new HealthBar(this);
	healthBar->transform.SetScale(3.5f, 3.0f);
	
	transform.SetScale(2.2f, 2.2f);

	collisionTag = EntityCollisionTag::Friendly;
}

void Player::Update() {
	transform.Move(transform.velocity.Normalize(), GetMoveSpeed());

	if (GetAttackingState() && SDL_GetTicks64() > GetNextAttackTick()) {
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		Vector2 mousePos(mouseX, mouseY);
		ShootArrow(mousePos);

		SetNextAttackTick(SDL_GetTicks64() + (GetAttackSpeed() * 1000));
	}
}

void Player::ShootArrow(const Vector2& targetPos) {
	int numberOfProjectiles = GetNumberOfProjectiles();
	float mainRotation = Vector2::AngleBetween(transform.GetScreenPosition(), targetPos);

	float spreadDistance = 1.30895833f / numberOfProjectiles; // this magic number is just PI/2.4 = ~75 degrees spread distance
	bool isEven = numberOfProjectiles % 2 == 0;

	for (int i = 0; i < numberOfProjectiles; ++i) {
		int multiplier = i - numberOfProjectiles/2;
		if (isEven && multiplier >= 0) ++multiplier;

		float offset = spreadDistance * multiplier;
		float rotation = mainRotation + offset;

		new Projectile(this, transform.GetPosition(), rotation, GetProjectileSpeed());
	}
}

void Player::OnKill() {
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
		if (GetSizeMultiplier() > 4.0f) return;
		SetSizeMultiplier(GetSizeMultiplier() * 1.05f);
		transform.SetScaleModifier(GetSizeMultiplier());
		break;
	case 1:
		if (GetMoveSpeed() > 100) return;
		SetMoveSpeed(GetMoveSpeed() * 1.05f);
		break;
	case 2:
		if (GetProjectileSpeed() > 160) return;
		SetProjectileSpeed(GetProjectileSpeed() * 1.05f);
		break;
	case 3:
		if (GetAttackSpeed() < 0.0001f) return;
		SetAttackSpeed(GetAttackSpeed() * 0.95f);
		break;
	case 4:
		SetMaxHealth(GetMaxHealth() * 1.25f);
		SetHealth(GetHealth() * 1.25f);
		break;
	case 5:
		SetNumberOfProjectiles(GetNumberOfProjectiles() + 1);
		break;
	}
}