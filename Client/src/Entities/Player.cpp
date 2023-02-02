#include "Player.h"
#include "Projectile.h"
#include "Monsters/Boar.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Mouse.h"
#include "../UI/UserInterface.h"
#include "../Managers/GameManager.h"
#include "../Managers/SceneManager.h"

Player::Player(std::string name) : Entity("assets/sprites/player.png", name) {
	isToBeDeletedOnSceneChange = false;
	Start();
}
Player::~Player() {
	CStats->Delete();
	CStats = nullptr;
	CHealth->Delete();
	CHealth = nullptr;
	CHealthBar->Delete();
	CHealthBar = nullptr;
}

void Player::Start() {
	// General
	collisionTag = EntityCollisionTag::Friendly;
	transform.SetScale(2.2f, 2.2f);
	
	// Stats Component
	CStats = AddComponent<Stats>();
	CStats->SetMoveSpeed(25.0f);
	CStats->SetProjectileSpeed(80);
	CStats->SetNumberOfProjectiles(1);
	CStats->SetAttackSpeed(0.3f);

	// Health Component
	CHealth = AddComponent<Health>();
	CHealth->SetMaxHealth(100);
	CHealth->SetHealth(100);

	// HealthBar Component
	CHealthBar = AddComponent<HealthBar>();
	CHealthBar->transform.SetScale(3.5f, 3.0f);
	CHealthBar->isToBeDeletedOnSceneChange = false;

	// Name Tag
	nameTag.AssignTransform(&transform);
	nameTag.SetText(name, SDL_Color{0, 0, 0});
	nameTag.SetOffset(0, -75);
	nameTag.SetFontSize(10);
	nameTag.shouldDrawCentered = true;
}
void Player::Update() {
	transform.Move(transform.velocity.Normalize(), CStats->GetMoveSpeed());

	if (CStats->GetAttackingState() && attackTimer.GetTimeMS() > (CStats->GetAttackSpeed() * 1000)) {
		ShootArrow(Mouse::GetPosition());
		attackTimer.Reset();
	}
}
void Player::Render() {
	renderer.Render();
	nameTag.Render();
}

void Player::Leech(float damageAmount) {
	float leechPercentage = CStats->GetLeech();
	float leechAmount = damageAmount * leechPercentage;

	float hp = CHealth->GetHealth() + leechAmount;
	float maxHP = CHealth->GetMaxHealth();
	if (hp > maxHP) hp = maxHP;

	CHealth->SetHealth(hp);
}
void Player::ShootArrow(const Vector2& targetPos) {
	int numberOfProjectiles = CStats->GetNumberOfProjectiles();
	float mainRotation = Vector2::AngleBetween(transform.GetScreenPosition(), targetPos);

	// used to be 1.30895833f or PI/2.4 = ~75 degrees spread.
	float spreadDistance = (3.1415f * CStats->GetProjectileSpread()) / numberOfProjectiles;
	bool isEven = numberOfProjectiles % 2 == 0;

	static float previousOffset = -999;
	static float epsilon = 0.025f;
	Projectile* lastInstantiatedProjectile = nullptr;
	previousOffset = -999;
	for (int i = 0; i < numberOfProjectiles; ++i) {
		int multiplier = i - numberOfProjectiles/2;
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
		lastInstantiatedProjectile = new Projectile(this, transform.GetPosition(), rotation, CStats->GetProjectileSpeed());
	}
}
void Player::GainXP(float value) {
	float xp = CStats->GetXP();
	float maxXP = CStats->GetMaxXP();
	xp += RandomFloat(value) * CStats->GetXPMultiplier();

	while (xp >= maxXP) {
		xp -= maxXP;
		maxXP *= 1.49f;
		CStats->SetMaxXP(maxXP);

		LevelUp();
	}

	CStats->SetXP(xp);
}
void Player::LevelUp() {
	CHealth->SetMaxHealth(CHealth->GetBaseMaxHealth() + 12);
	CHealth->SetHealth(CHealth->GetBaseMaxHealth());
	CStats->SetLevel(CStats->GetLevel() + 1);

	OnLevelUp();
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
		if (CStats->GetSizeMultiplier() > 4.0f) return;
		CStats->SetSizeMultiplier(CStats->GetSizeMultiplier() * 1.05f);
		break;
	case 1:
		if (CStats->GetMoveSpeed() > 100) return;
		CStats->SetMoveSpeed(CStats->GetMoveSpeed() * 1.05f);
		break;
	case 2:
		if (CStats->GetProjectileSpeed() > 300) return;
		CStats->SetProjectileSpeed(CStats->GetProjectileSpeed() * 1.05f);
		break;
	case 3:
		if (CStats->GetAttackSpeed() < 0.0001f) return;
		CStats->SetAttackSpeed(CStats->GetAttackSpeed() * 0.95f);
		break;
	case 4:
		CHealth->SetHealthMultiplier(CHealth->GetHealthMultiplier() * 1.25f);
		break;
	case 5:
		if (CStats->GetNumberOfProjectiles() > 10000) return;
		CStats->SetNumberOfProjectiles(CStats->GetNumberOfProjectiles() + 1);
		break;
	}
}

// Events
void Player::OnLevelUp() {
	// Show Power-up Options
	GAME.PauseGame(true);
	UI.HideTooltip();
	UI.UpdatePowerUps();
	UI.ShowPowerUps();
}
void Player::OnDeath() {
	int lastStandCount = CStats->GetLastStandCount();
	if (lastStandCount > 0) {
		CHealth->SetGuardianAngel(3);
		--CStats->lastStandCount;
		return;
	}

	SceneMgr.OnPlayerDeath();
}
void Player::OnKill() {
	++CStats->totalKills;
	GainXP(1);

	if (CStats->HasHH()) FUN_Headhunter();
}