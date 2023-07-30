#include "Monster.h"
#include "Explosions/Explosion.h"
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
	rarity = RandomEnum(MonsterRarity::Count);
	transform.SetScale((int)(rarity) * 0.40f + 2, (int)(rarity) * 0.40f + 2);

	// Stats Component
	CStats = AddComponent<Stats>();
	CStats->SetMoveSpeed(200.0f - ((int)rarity * 15.67f));

	// Health Component
	CHealth = AddComponent<Health>();
	CHealth->SetMaxHealth(10 + RandomInt(0, ((int)rarity * 17.45f)));
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
	// Retrieve various stats and information.
	Stats* playerStats = GAME.GetPlayer()->CStats;
	float playerLuck = playerStats->GetIIR();
	float playerChanceDoubleLoot = playerStats->GetChanceToDoubleLoot();
	int monsterLevel = CStats->GetLevel();

	// Manipulate Loot if EnhancedLoot stat boolean is enabled by powerups.
	if (CStats->dropsEnhancedLoot) {
		lootChance *= 1.30f;
		monsterLevel = (int)(monsterLevel * 1.30f);
	}

	// Multiply Loot Chance with Player's luck.
	lootChance *= playerLuck;
	
	// Calculate the number of items to drop.
	int numberOfItemsToDrop = (int)(lootChance / 1.0f);// + (> RandomFloat(1.0f) ? 1: 0);
	float remainingLootChance = lootChance - numberOfItemsToDrop;
	numberOfItemsToDrop += remainingLootChance > RandomFloat(0, 1.0f) ? 1: 0;

	// If the player hit the jackpot, lets double their loot amount.
	if (playerChanceDoubleLoot > RandomFloat(0, 1.0f))
		numberOfItemsToDrop *= 2.0f;

	// Drop Items, poggies!
	for (; numberOfItemsToDrop >= 0; --numberOfItemsToDrop)
		Item::DropItem(monsterLevel, transform.GetPosition() + RandomVector(25.0f));
	
	// Create explosions! Woohoo!!!
	(new Explosion())->transform.SetPosition(transform.GetPosition());

	// Delete the entity.
	Delete();
}