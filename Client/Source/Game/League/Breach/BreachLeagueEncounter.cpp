#include "BreachLeagueEncounter.h"
#include "../../../Managers/GameManager.h"
#include "../../../Managers/EntityManager.h"
#include "../../../Miscellaneous/Random.h"

BreachLeagueEncounter::BreachLeagueEncounter() : Entity("Assets/Sprites/Monsters/38.png", "BreachEncounter") {
	isAutoUpdateEnabled = false;
	totalNumberOfSpawns = RandomFloat(100, 5000);
	eachWaveSpawnCount = totalNumberOfSpawns / (int)maxExpandRadius;
}

void BreachLeagueEncounter::Update() {
	if (currentState == Idle) {
		auto player = GAME.GetPlayer();
		float distanceToPlayer = player->transform.GetPosition().DistanceToFast(transform.GetPosition());

		if (distanceToPlayer < 30.0f)
			StartEncounter();
	}
	else if (currentState == Expanding) Expand();
	else if (currentState == Shrinking) Shrink();

	renderer.Render();

	// [@todo] TEMP debug draw bounds
	{
		int w = renderer.GetWidth() * renderer.localScale.x;
		int h = renderer.GetHeight() * renderer.localScale.y;
		Vector2 pos = transform.GetScreenPosition();
		GAME.DrawRect(pos.x - w / 2, pos.y - h / 2, w, h, { 255, 0, 0 });
	}
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
	// Expand!
	currentRadius += Time::deltaTime;
	if (currentRadius >= maxExpandRadius) {
		currentRadius = maxExpandRadius;
		currentState = Shrinking;
		return;
	}

	// Scale up the Breach
	renderer.SetScale(currentRadius, currentRadius);

	// On each Discrete number (of current radius) while we are expanding, spawn monsters.
	static int lastDiscreteIndex = 0;
	int currentDiscrete = (int)currentRadius;
	if (lastDiscreteIndex != currentDiscrete) {
		lastDiscreteIndex = currentDiscrete;

		// Spawn Monsters
		const Vector2& pos = transform.GetPosition();
		int w = (renderer.GetWidth() * renderer.localScale.x) / 2;
		int h = (renderer.GetHeight() * renderer.localScale.y) / 2;
		for (int i = 0; i < eachWaveSpawnCount; ++i) {
			BreachMonster* newMonster = new BreachMonster();
			float randomAngle = RandomFloat(-3.1415f, 3.1415f);
			float randomX = cos(randomAngle) * w;
			float randomY = sin(randomAngle) * h;
			newMonster->transform.SetPosition(pos.x + randomX, pos.y + randomY);
		}
	}
}
void BreachLeagueEncounter::Shrink() {
	// Shrink!
	currentRadius -= Time::deltaTime;
	if (currentRadius <= 0.016f) {
		currentRadius = 0.0f;
		EndEncounter();
		return;
	}

	// Scale down the Breach
	renderer.SetScale(currentRadius, currentRadius);

	// On each Discrete number (of current radius) while we are shrinking, delete most-outer monsters.
	static int lastDiscreteIndex = 0;
	int currentDiscrete = (int)currentRadius;
	if (lastDiscreteIndex != currentDiscrete) {
		lastDiscreteIndex = currentDiscrete;

		// Calculate the distance to the most outer ring.
		const Vector2& pos = transform.GetPosition();
		float ringHeight = renderer.GetHeight() * renderer.localScale.y;
		float ringRadius = ringHeight / 2; // let's assume the ring is a perfect circle so width = height.

		// Delete the monsters that are out of the outer ring
		for (auto& monster : EntityMgr.FindAll(EntityFlags::IsBreachLeagueSpecific))
			if (pos.DistanceToFast(monster->transform.GetPosition()) > ringRadius)
				monster->Delete();
	}
}

// Clear&Delete all the remaining spawned monsters.
void BreachLeagueEncounter::ClearAllSpawnedMonsters() {
	auto allBreachMonsters = EntityMgr.FindAll(EntityFlags::IsBreachLeagueSpecific);
	for (auto& monster : allBreachMonsters)
		monster->Delete();
}