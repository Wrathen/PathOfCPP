#include "Monster.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Random.h"
#include "../Game/Item/Item.h"

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
	healthBar->isToBeDeletedOnSceneChange = false;

	// Box Collider
	collider = AddComponent<BoxCollider>();

	// Name Tag
	nameTag.AssignTransform(&transform);
	nameTag.SetText(name, SDL_Color{ 0, 0, 0 });
	nameTag.SetOffset(0, -75);
	nameTag.SetFontSize(10);
	nameTag.shouldDrawCentered = true;

	// AI
	moveTowardsTarget = AddComponent<MoveTowardsTarget>();
	moveTowardsTarget->SetTarget(GAME.GetPlayer());

	collisionTag = EntityCollisionTag::Hostile;
}

void Monster::Update() {
	moveTowardsTarget->Update();
}
void Monster::Render() {
	renderer.Render();
	nameTag.Render();
}

void Monster::OnDeath() {
	if (lootChance > RandomFloat(1.0f))
		Item::DropItem(stats->GetLevel(), transform.GetPosition());
}