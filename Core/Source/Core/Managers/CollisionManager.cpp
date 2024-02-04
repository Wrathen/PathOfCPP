#include "CollisionManager.h"
#include "SceneManager.h"
#include "Core/Game/Component/Components.h"

namespace Core {
	// Adds static colliders based on zone data.
	void CollisionManager::AddStaticColliders(const std::vector<ZoneColliderData>& colliders) {
		staticColliders = colliders;
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

	// @todo clear out all -2000's from the codebase.
	CollisionResult CollisionManager::IsPositionOccupied(const Rect& rect) {
		// @todo we should use SpatialHash instead of Bruteforce.
		for (size_t i = 0; i < staticColliders.size(); ++i) {
			auto& col = staticColliders[i];
			Rect colRect { (int)col.position.x - 2000, (int)col.position.y - 2000, (int)col.w, (int)col.h };
			CollisionResult result = colRect.Intersects(rect);
			
			// If there was a collision, return the collision result.
			if (result) 
				return result;
		}

		// No collision were found, return a null object.
		return CollisionResult();
	}
}