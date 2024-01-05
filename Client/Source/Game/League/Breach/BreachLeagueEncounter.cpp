#include "BreachLeagueEncounter.h"
#include "../../../Managers/GameManager.h"
#include "../../../Managers/EntityManager.h"
#include "../../../Miscellaneous/Random.h"
#include "Behaviour/Leagues/Breach/BreachMonsterAI.h"

BreachLeagueEncounter::BreachLeagueEncounter() : Entity("Assets/Sprites/Monsters/38.png", "BreachEncounter") {
	isAutoUpdateEnabled = false;
	totalNumberOfSpawns = RandomFloat(100, 5000);
	eachWaveSpawnCount = (totalNumberOfSpawns / (int)maxExpandRadius) / 4; // I divide by 4 here because my tick timers are at 0.250f;

	allMonsters.reserve(totalNumberOfSpawns);
}

void BreachLeagueEncounter::Update() {
	Entity::Update();

	if (currentState == Idle) {
		auto player = GAME.GetPlayer();
		float distanceToPlayer = player->transform.GetPosition().DistanceToFast(transform.GetPosition());

		if (distanceToPlayer < 30.0f)
			StartEncounter();
	}
	else if (currentState == Expanding) Expand();
	else if (currentState == Shrinking) Shrink();

	// Scale the Breach to the current radius and render it.
	renderer.SetScale(currentRadius, currentRadius);
	renderer.Render();

	// [@todo] TEMP debug draw bounds
	{
		int w = renderer.GetWidth() * renderer.localScale.x;
		int h = renderer.GetHeight() * renderer.localScale.y;
		Vector2 pos = transform.GetScreenPosition();
		GAME.DrawRect(pos.x - w / 2, pos.y - h / 2, w, h, { 255, 0, 0 });
	}

	// Track a timer for tick.
	static float timer = 0;
	if (timer < 0.250f) {
		timer += Time::deltaTime;
		return;
	}

	// Reset the Timer.
	timer = 0;

	if (currentState == Expanding) OnExpandTick();
	else if (currentState == Shrinking) OnShrinkTick();
}

void BreachLeagueEncounter::StartEncounter() {
	currentState = Expanding;
}
void BreachLeagueEncounter::EndEncounter() {
	currentState = Ended;
	ClearAllSpawnedMonsters();
	Delete();
}

void BreachLeagueEncounter::Expand() {
	currentRadius += Time::deltaTime;
	if (currentRadius >= maxExpandRadius) {
		currentRadius = maxExpandRadius;
		currentState = Shrinking;
		return;
	}
}
void BreachLeagueEncounter::Shrink() {
	currentRadius -= Time::deltaTime;
	if (currentRadius <= 0.016f) {
		currentRadius = 0.0f;
		EndEncounter();
		return;
	}
}

void BreachLeagueEncounter::OnExpandTick() {
	const Vector2& pos = transform.GetPosition();
	int w = (renderer.GetWidth() * renderer.localScale.x) / 2;
	int h = (renderer.GetHeight() * renderer.localScale.y) / 2;

	for (int i = 0; i < eachWaveSpawnCount; ++i) {
		float randomAngle = RandomFloat(-3.1415f, 3.1415f);
		float posX = pos.x + cos(randomAngle) * w;
		float posY = pos.y + sin(randomAngle) * h;

		CreateBreachMonster(posX, posY);
	}
}

void BreachLeagueEncounter::OnShrinkTick() {
	for (size_t i = 0; i < allMonsters.size(); ++i)
		if (allMonsters[i] && !allMonsters[i]->isToBeDeleted)
			allMonsters[i]->breachMonsterAI->OnShrinkTick(GetRadius());
}

void BreachLeagueEncounter::OnOutOfRange(BreachMonster* monster) {
	if (currentState == Shrinking)
		DeleteBreachMonster(monster);
}

void BreachLeagueEncounter::CreateBreachMonster(float posX, float posY) {
	// Create a New Breach Monster. Base CTORs handle collection safe pointers.
	BreachMonster* newMonster = new BreachMonster();

	// Gather the shared pointer from collection.
	std::shared_ptr<Entity> newMonsterBasePTR = EntityMgr.GetFast(newMonster->guid);

	// Cast to BreachMonster pointer type.
	std::shared_ptr<BreachMonster> newMonsterPTR = std::static_pointer_cast<BreachMonster>(newMonsterBasePTR);

	// Set the position of the newly created monster.
	newMonsterPTR->transform.SetPosition(posX, posY);

	// Add breach specific AI behaviour into it.
	newMonsterPTR->breachMonsterAI = new BreachMonsterAI();
	newMonsterPTR->breachMonsterAI->parentBreach = this;
	newMonsterPTR->breachMonsterAI->parentMonster = newMonster;

	// Add the pointer into our storage vector.
	allMonsters.emplace_back(newMonsterPTR);
}

void BreachLeagueEncounter::DeleteBreachMonster(BreachMonster* monster) {
	if (!monster || monster->isToBeDeleted) return;

	for (size_t i = 0; i < allMonsters.size(); ++i) {
		if (monster == allMonsters[i].get()) {
			monster->Delete();
			allMonsters[i] = nullptr;
		}
	}
}

float BreachLeagueEncounter::GetRadius() {
	float ringHeight = renderer.GetHeight() * renderer.localScale.y;
	float ringRadius = ringHeight / 2; // let's assume the ring is a perfect circle so width = height.

	return ringRadius;
}

// Clear&Delete all the remaining spawned monsters.
void BreachLeagueEncounter::ClearAllSpawnedMonsters() {
	for (auto& monster : allMonsters)
		DeleteBreachMonster(monster.get());

	allMonsters.clear();
}