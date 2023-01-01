#include "CollisionManager.h"

void CollisionManager::ResetSpatialHash() {
	spatialHash.Clear();

	for (auto& collider : *GetAll()) {
		if (collider.second->source->isToBeDeleted) continue;
		spatialHash.Insert(collider.second->source);
	}
}

void CollisionManager::Update() {
	Collection::Update();
	ResetSpatialHash();
}