#include "Monster.h"
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Random.h"
#include "../Miscellaneous/Log.h"

Monster::Monster(std::string name): Entity(name) { Start(); }
Monster::Monster(std::string texturePath, std::string name): Entity(texturePath, name) { Start(); }

void Monster::Start() {
	stats = new MonsterStats();
	stats->moveSpeed = 8.0f;
	stats->health = RandomInt(stats->maxHealth) + 1;

	healthBar = new HealthBar(this);
	healthBar->transform.SetScale(3.5f, 3.0f);

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