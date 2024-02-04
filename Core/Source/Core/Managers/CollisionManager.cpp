#include "CollisionManager.h"
#include "SceneManager.h"
#include "Core/Game/Component/Components.h"

namespace Core {
	// Adds static colliders based on zone data.
	void CollisionManager::AddStaticColliders(const std::vector<ZoneColliderData>& colliders) {
		staticColliders = colliders;
	
		staticCollidersSpatialHash.Clear();
		for (auto& data : colliders)
			staticCollidersSpatialHash.Add(data, (int)data.position.x, (int)data.position.y, (int)data.w, (int)data.h);
	}

	void CollisionManager::ResetSpatialHash() {
		spatialHash.Clear();

		// Get the current scene entt registry.
		auto& reg = SceneMgr.GetCurrentScene()->reg;
		auto group = reg.group<BoxColliderComponent>(entt::get<TransformComponent>);

		group.each([&](auto entity, auto& _, auto& transform) {
			spatialHash.Insert(entity, (int)transform.position.x, (int)transform.position.y);
		});
	}

	void CollisionManager::Update() { ResetSpatialHash(); }
	void CollisionManager::UpdateCollection() { }

	CollisionResult CollisionManager::IsPositionOccupied(const Rect& rect) {
		// @todo we should use SpatialHash instead of Bruteforce.
		auto nearbyColliders = staticCollidersSpatialHash.Query(rect.x, rect.y, (float)rect.w);
		for (size_t i = 0; i < nearbyColliders.size(); ++i) {
			auto& col = nearbyColliders[i];
			Rect colRect { (int)col.position.x, (int)col.position.y, (int)col.w, (int)col.h };
			CollisionResult result = colRect.Intersects(rect);
			
			// If there was a collision, return the collision result.
			if (result) 
				return result;
		}

		// No collision were found, return a null object.
		return CollisionResult();
	}
}