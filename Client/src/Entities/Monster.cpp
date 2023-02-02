#include "Monster.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Random.h"
#include "../Game/Item/Item.h"

Monster::Monster(std::string name): Entity(name) { Start(); }
Monster::Monster(std::string texturePath, std::string name): Entity(texturePath, name) { Start(); }
Monster::~Monster() {
	CStats->Delete();
	CStats = nullptr;
	CHealth->Delete();
	CHealth = nullptr;
	CHealthBar->Delete();
	CHealthBar = nullptr;
	CMoveTowardsTarget->Delete();
	CMoveTowardsTarget = nullptr;
	CCollider->Delete();
	CCollider = nullptr;
}
void Monster::Start() {
	// General
	collisionTag = EntityCollisionTag::Hostile;
	rarity = ((MonsterRarity)RandomInt(4));
	transform.SetScale((int)(rarity) * 0.40f + 2, (int)(rarity) * 0.40f + 2);

	// Stats Component
	CStats = AddComponent<Stats>();
	CStats->SetMoveSpeed(11.0f - ((int)rarity * 1.67f));

	// Health Component
	CHealth = AddComponent<Health>();
	CHealth->SetMaxHealth(10 + RandomInt(((int)rarity * 17.45f)));
	CHealth->SetHealth(CHealth->GetMaxHealth());

	// Healthbar Component
	CHealthBar = AddComponent<HealthBar>();
	CHealthBar->transform.SetScale(3.5f, 3.0f);
	CHealthBar->isToBeDeletedOnSceneChange = false;

	// Box Collider Component
	CCollider = AddComponent<BoxCollider>();

	// Name Tag
	nameTag.AssignTransform(&transform);
	nameTag.SetText(name + " (HP" + std::to_string((int)CHealth->GetMaxHealth()) + ")", SDL_Color{0, 0, 0});
	nameTag.SetOffset(0, -75);
	nameTag.SetFontSize(10);
	nameTag.shouldDrawCentered = true;

	// AI
	CMoveTowardsTarget = AddComponent<MoveTowardsTarget>();
	CMoveTowardsTarget->SetTarget(GAME.GetPlayer());
}

void Monster::Update() { CMoveTowardsTarget->Update(); }
void Monster::Render() {
	renderer.Render();
	nameTag.Render();
}

void Monster::OnDeath() {
	auto playerStats = GAME.GetPlayer()->CStats;
	auto playerLuck = playerStats->GetLuck();
	auto playerChanceDoubleLoot = playerStats->GetChanceToDoubleLoot();

	auto monsterLevel = CStats->GetLevel();
	if (CStats->dropsEnhancedLoot) {
		lootChance *= 1.30f;
		monsterLevel = (int)(monsterLevel * 1.30f);
	}

	lootChance *= playerLuck;

	if (lootChance > RandomFloat(1.0f))
		Item::DropItem(monsterLevel, transform.GetPosition() + RandomVector(3.0f));
	if (playerChanceDoubleLoot > RandomFloat(1.0f))
		Item::DropItem(monsterLevel, transform.GetPosition() + RandomVector(3.0f));
	
	Delete();
}