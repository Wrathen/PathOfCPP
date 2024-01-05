#include "CollisionManager.h"
#include "CameraManager.h"

// Adds static colliders based on zone data.
void CollisionManager::AddStaticColliders(const std::vector<ZoneColliderData>& colliders) {
	staticColliders = colliders;
}

void CollisionManager::ResetSpatialHash() {
	spatialHash.Clear();

	for (auto& collider : GetAll()) {
		if (collider->source->isToBeDeleted) continue;
		spatialHash.Insert(collider->source);
	}

	//spatialHash.RenderDebug();
}

void CollisionManager::Update() { ResetSpatialHash(); }
void CollisionManager::UpdateCollection() { Collection::Update(); }

// @todo Will use SpatialHash soon instead of this bruteforce approach
// @todo clear out all -2000's from the codebase.
bool CollisionManager::IsPositionMovable(const Rect& rect) {
	for (size_t i = 0; i < staticColliders.size(); ++i) {
		auto& col = staticColliders[i];
		if (Rect::IntersectsRect(col.position.x - 2000, col.position.y - 2000, col.w, col.h, rect.x, rect.y, rect.w, rect.h)) {
			//GAME.DrawRect(col.position - Vector2{2000, 2000}, col.w, col.h);
			GAME.DrawRect(col.position - Vector2{2000, 2000} - Camera.GetPosition(), col.w, col.h, {255, 0, 0});
			return false;
		}
	}

	return true;
}