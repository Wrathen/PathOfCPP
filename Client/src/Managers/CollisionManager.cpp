#include "CollisionManager.h"

void CollisionManager::ResetSpatialHash() {
	spatialHash.Clear();

	for (auto& collider : *GetAll()) {
		if (collider->source->isToBeDeleted) continue;
		spatialHash.Insert(collider->source);
	}

	//spatialHash.RenderDebug();
}

void CollisionManager::Update() {
	Collection::Update();
	ResetSpatialHash();
}