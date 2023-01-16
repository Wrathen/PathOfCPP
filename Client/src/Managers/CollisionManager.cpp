#include "CollisionManager.h"

void CollisionManager::ResetSpatialHash() {
	spatialHash.Clear();

	for (auto& collider : *GetAll()) {
		if (collider->source->isToBeDeleted) continue;
		spatialHash.Insert(collider->source);
	}
}

void CollisionManager::Update() {
	Collection::Update();
	ResetSpatialHash();
}