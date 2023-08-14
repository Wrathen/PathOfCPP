#include "BreachLeagueEncounter.h"
#include "../../../Managers/GameManager.h"

BreachLeagueEncounter::BreachLeagueEncounter() : Entity("Assets/Sprites/Monsters/38.png", "BreachEncounter") { 
	isAutoUpdateEnabled = false;
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
}
void BreachLeagueEncounter::StartEncounter() {
	currentState = Expanding;
}
void BreachLeagueEncounter::EndEncounter() {
	currentState = Ended;
	Delete();
}

void BreachLeagueEncounter::Expand() {
	currentRadius += Time::deltaTime;
	if (currentRadius >= 5.0f) {
		currentRadius = 5.0f;
		currentState = Shrinking;
	}

	renderer.SetScale(currentRadius, currentRadius);
}
void BreachLeagueEncounter::Shrink() {
	currentRadius -= 5.0f * Time::deltaTime;
	if (currentRadius <= 0.016f) {
		currentRadius = 0.0f;
		EndEncounter();
	}

	renderer.SetScale(currentRadius, currentRadius);
}