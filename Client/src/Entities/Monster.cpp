#include "Monster.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Log.h"

Monster::Monster(std::string name): Entity(name) { Start(); }
Monster::Monster(std::string texturePath, std::string name): Entity(texturePath, name) { Start(); }

void Monster::Start() {
	// Rarity & Related
	rarity = ((MonsterRarity)RandomInt(4));
	transform.SetScale((int)(rarity) * 0.40f + 2, (int)(rarity) * 0.40f + 2);

	// Stats
	SetMoveSpeed(8.0f + ((int)rarity * 2.0f));
	SetMaxHealth(100 + ((int)rarity * 27.45f));
	SetHealth(RandomInt(GetMaxHealth()) + 1);

	// Healthbar
	healthBar = new HealthBar(this);
	healthBar->transform.SetScale(3.5f, 3.0f);

	// AI
	moveTowardsTarget.SetSource(this);
	moveTowardsTarget.SetTarget((Entity*)GAME.GetPlayer());

	// [To:Do] Delete--Debug
	int randx = RandomInt(3778) - 3778 / 2;
	int randy = RandomInt(3778) - 3778 / 2;

	//Debug(std::to_string(randx) + ", " + std::to_string(randy));
	transform.SetPosition(randx, randy);

	collisionTag = EntityCollisionTag::Hostile;
}

void Monster::Update() {
	moveTowardsTarget.Update();
}