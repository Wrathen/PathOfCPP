#include "Player.h"
#include "Projectile.h"
#include "Monsters/Boar.h"
#include "../Miscellaneous/Log.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Mouse.h"
#include "../UI/UserInterface.h"
#include "../Managers/GameManager.h"
#include "../Managers/SceneManager.h"
#include "../Managers/CollisionManager.h"
#include "../Managers/CameraManager.h"
#include "../Managers/InputManager.h"

Player::Player(std::string name) : Entity("Assets/Sprites/player.png", name) {
	flags = EntityFlags::IsPlayer | EntityFlags::IsHittable;
	
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
	CAnimator->Delete();
	CAnimator = nullptr;
	CCollider->Delete();
	CCollider = nullptr;
}

void Player::Start() {
	// General
	flags = EntityFlags::IsPlayer | EntityFlags::IsHittable;
	transform.SetScale(2.2f, 2.2f);

	// Stats Component
	CStats = AddComponent<Stats>();
	CStats->ResetPowerUps();

	// Health Component
	CHealth = AddComponent<Health>();
	CHealth->SetMaxHealth(100);
	CHealth->SetHealth(100);

	// HealthBar Component
	CHealthBar = AddComponent<HealthBar>();
	CHealthBar->transform.SetScale(3.5f, 3.0f);
	CHealthBar->isToBeDeletedOnSceneChange = false;

	// Animator Component
	CAnimator = AddComponent<Animator>();
	CAnimator->Add(Animation("Idle", 120, 64, 64, 0, 0, 9, 0, true));
	CAnimator->Add(Animation("Move", 30, 64, 64, 0, 1, 3, 1, true));
	CAnimator->Add(Animation("Attack", 10, 64, 64, 0, 2, 3, 2, false));

	// Collider Component
	CCollider = AddComponent<BoxCollider>();
	CCollider->SetWidth(16);
	CCollider->SetHeight(16);

	// Name Tag
	nameTag.AssignTransform(&transform);
	nameTag.SetText(name, SDL_Color{ 255, 255, 255 });
	nameTag.SetOffset(0, -75);
	nameTag.SetFontSize(10);
	nameTag.shouldDrawCentered = true;

	// @TODO delete this later TEST - TEMP
	{
		// Add ShootArrow ability
		AddAbility("ShootArrow");
		AssignAbilityToInputSlot("ShootArrow", 0);
	}
}
void Player::Update() {
	Entity::Update();

	CHEAT_Codes();
	CAnimator->Update();

	// Flip the character based on mouse position.
	Vector2 mousePos = Mouse::GetPosition();
	Vector2 playerPos = transform.GetScreenPosition();
	renderer.isFlipped = mousePos.x > playerPos.x;

	// Shoot
	if (CStats->GetAttackingState() && attackTimer.GetTimeMS() > (CStats->GetAttackSpeed() * 1000)) {
		CAnimator->Play("Attack", true);
		CastAbility(0); // 0 means Left mouse button (LMB for short). Check Entity.h for more explanation.
		attackTimer.Reset();
	}

	// Move and Update Animator States.
	Vector2 velocityNormalized = transform.velocity.Normalize();
	if (velocityNormalized.Magnitude() > 0.01f) {
		// Check if the target position is movable.
		Vector2 nextFramePosition = transform.GetPositionNextFrame(velocityNormalized, CStats->GetMoveSpeed());
		const auto& boundaries = CCollider->GetBoundaries();
		if (!CollisionMgr.IsPositionMovable(Rect(nextFramePosition.x - boundaries.w / 2,
												 nextFramePosition.y - boundaries.h / 2,
												 boundaries.w, boundaries.h))) return;

		// Set position and play move animation.
		transform.SetPosition(nextFramePosition);
		CAnimator->Play("Move");
	}
	else CAnimator->Play("Idle");
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
void Player::GainXP(float value) {
	float xp = CStats->GetXP();
	float maxXP = CStats->GetMaxXP();
	xp += RandomFloat(0, value) * CStats->GetXPMultiplier();

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
	float hhChance = CStats->GetHHChance() + CStats->GetReplicaHHChance();
	bool shouldStealBuff = hhChance > RandomFloat(0, 1.0f);
	if (!shouldStealBuff) return;

	int rnd = RandomInt(0, 6);
	switch (rnd) {
	case 0:
		if (CStats->GetSizeMultiplier() > 4.0f) return;
		CStats->SetSizeMultiplier(CStats->GetSizeMultiplier() * 1.05f);
		break;
	case 1:
		if (CStats->GetMoveSpeed() > 1500) return;
		CStats->SetMoveSpeed(CStats->GetMoveSpeed() * 1.05f);
		break;
	case 2:
		if (CStats->GetProjectileSpeed() > 2000) return;
		CStats->SetProjectileSpeed(CStats->GetProjectileSpeed() * 1.05f);
		break;
	case 3:
		if (CStats->GetAttackSpeed() < 0.0001f) return;
		CStats->SetAttackSpeed(CStats->GetAttackSpeed() * 0.95f);
		break;
	case 4:
		if (CHealth->GetHealthMultiplier() > 100.0f) return;
		CHealth->SetHealthMultiplier(CHealth->GetHealthMultiplier() * 1.25f);
		break;
	case 5:
		if (CStats->GetNumberOfProjectiles() > 1000) return;
		CStats->SetNumberOfProjectiles(CStats->GetNumberOfProjectiles() + 1);
		break;
	}
}

void Player::CHEAT_Codes() {
	// Cheat Stuff, hehe
	if (InputMgr.IsKeyHeld(SDLK_f))
		CStats->SetNumberOfProjectiles(CStats->GetNumberOfProjectiles() + 1);
	else if (InputMgr.IsKeyHeld(SDLK_g))
		CStats->projectileSpreadMultiplier *= 1.001f;
}

// Events
void Player::OnMouseDown() {
	CStats->SetAttackingState(true);
}
void Player::OnMouseUp() {
	CStats->SetAttackingState(false);
}
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