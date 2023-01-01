#include "EntityManager.h"
#include "CollisionManager.h"
#include "../Miscellaneous/Log.h"

void EntityManager::Update() {
	Collection::Update();

	for (auto& entity : *GetAll()) {
		auto& e = *entity.second;
		//auto ePos = e.transform.GetScreenPosition();
		//bool isEligible = true;
		//auto nearbyEntities = CollisionMgr.spatialHash.Query(ePos.x, ePos.y, 1, 1);
		//if (nearbyEntities.size() > 1) isEligible = false;

		e.Update();

		//if (isEligible) {
		e.Render();
		//}
		
	}
}