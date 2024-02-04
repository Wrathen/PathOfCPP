#pragma once
#include <entt.hpp>
#include <vector>
#include "Core/Miscellaneous/SpatialHash.h"
#include "Core/Miscellaneous/NewSpatialHash.h"
#include "Core/Game/Zone/Zone.h"

namespace Core {
	#define CollisionMgr CollisionManager::GetInstance()
	class CollisionManager {
	public:
		static CollisionManager& GetInstance() { static CollisionManager _i; return _i; }

		std::vector<ZoneColliderData> staticColliders;
		SpatialHash<entt::entity> spatialHash{ 4000, 4000, 80 };
		NewSpatialHash<ZoneColliderData> staticCollidersSpatialHash { 4000u, 500u };

		void AddStaticColliders(const std::vector<ZoneColliderData>& colliders);
		void ResetSpatialHash();
		void Update();
		void UpdateCollection();

		CollisionResult IsPositionOccupied(const Rect& rect);

	private:
		CollisionManager() {}
		~CollisionManager() {}
		CollisionManager(CollisionManager const&) = delete;
		void operator=(CollisionManager const&) = delete;
	};
}