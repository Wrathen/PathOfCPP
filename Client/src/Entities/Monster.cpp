#include "Monster.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Random.h"

Monster::Monster(std::string name): Entity(name) { Start(); }
Monster::Monster(std::string texturePath, std::string name): Entity(texturePath, name) { Start(); }
Monster::~Monster() {
	healthBar->Delete();
	healthBar = nullptr;
	collider->Delete();
	collider = nullptr;
}
void Monster::Start() {
	// Rarity & Related
	rarity = ((MonsterRarity)RandomInt(4));
	transform.SetScale((int)(rarity) * 0.40f + 2, (int)(rarity) * 0.40f + 2);

	// Stats
	stats = AddComponent<Stats>();
	stats->SetMoveSpeed(8.0f + ((int)rarity * 2.0f));
	stats->SetMaxHealth(100 + ((int)rarity * 27.45f));
	stats->SetHealth(RandomInt(stats->GetMaxHealth()) + 1);

	// Healthbar
	healthBar = AddComponent<HealthBar>();
	healthBar->transform.SetScale(3.5f, 3.0f);

	// Box Collider
	collider = AddComponent<BoxCollider>();

	// AI
	moveTowardsTarget = AddComponent<MoveTowardsTarget>();
	moveTowardsTarget->SetTarget(GAME.GetPlayer());

	collisionTag = EntityCollisionTag::Hostile;
}

void Monster::Update() {
	moveTowardsTarget->Update();
}