#include "BreachLeague.h"

void BreachLeague::Init() {
	CreateNewBreach();
}
void BreachLeague::Update() {
	if (!encounter) return;

	if (encounter->isToBeDeleted) {
		encounter = nullptr;
		CreateNewBreach();
		return;
	}

	encounter->Update();
}

void BreachLeague::CreateNewBreach() {
	if (encounter) return;
	encounter = new BreachLeagueEncounter();
	encounter->transform.SetPosition(Vector2::RandomVector(-100.0f, 100.0f));
}