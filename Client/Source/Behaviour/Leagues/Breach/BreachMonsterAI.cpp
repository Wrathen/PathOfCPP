#include "BreachMonsterAI.h"
#include "Game/League/Breach/BreachLeagueEncounter.h"

void BreachMonsterAI::OnShrinkTick(float breachRadius) {
	// If the parent breach does not exist, return.
	if (!parentBreach) return;
	if (!parentMonster || parentMonster->isToBeDeleted) return;

	float distance = parentMonster->transform.GetPosition().DistanceToFast(parentBreach->transform.GetPosition());
	
	if (distance > breachRadius) {
		BreachMonster* parentMonsterPtr = static_cast<BreachMonster*>(parentMonster);
		BreachLeagueEncounter* parentBreachPtr = static_cast<BreachLeagueEncounter*>(parentBreach);

		parentBreachPtr->OnOutOfRange(parentMonsterPtr);
	}
}