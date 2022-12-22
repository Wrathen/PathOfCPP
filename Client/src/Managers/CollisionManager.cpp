#include "CollisionManager.h"

void CollisionManager::ResetSpatialHash() {
	spatialHash.Clear();

	for (auto& collider : *GetAll()) {
		if (collider.second->entity->isToBeDeleted) continue;
		spatialHash.Insert(collider.second->entity);
	}
}

void CollisionManager::Update() {
	Collection::Update();
	ResetSpatialHash();
}