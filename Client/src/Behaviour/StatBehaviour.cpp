#include "StatBehaviour.h"

// Constructor&Deconstructor
StatBehaviour::StatBehaviour() { stats = new Stats(); }
StatBehaviour::~StatBehaviour() { delete stats; stats = nullptr; }

void StatBehaviour::TakeDamage(float dmg) {
	stats->health -= dmg;
	if (stats->health <= 0) Die();
}
void StatBehaviour::Die() {
	Debug("I died poggies");
}