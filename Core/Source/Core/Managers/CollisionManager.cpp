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

		for (auto& entity : group) {
			auto& entityPos = reg.get<TransformComponent>(entity).position;
			spatialHash.Insert(entity, (int)entityPos.x, (int)entityPos.y);
		}

		//spatialHash.RenderDebug();
	}

	void CollisionManager::Update() { ResetSpatialHash(); }
	void CollisionManager::UpdateCollection() { }

	// @todo Will use SpatialHash soon instead of this bruteforce approach
	// @todo clear out all -2000's from the codebase.
	bool CollisionManager::IsPositionMovable(const Rect& rect) {
		for (size_t i = 0; i < staticColliders.size(); ++i) {
			auto& col = staticColliders[i];
			bool intersects = Rect::IntersectsRect((int)col.position.x - 2000, (int)col.position.y - 2000, col.w, col.h,
												   rect.x, rect.y, rect.w, rect.h);
			
			if (intersects) return false;
		}

		return true;
	}
}