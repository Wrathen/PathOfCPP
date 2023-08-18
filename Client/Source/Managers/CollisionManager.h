#pragma once
#include <vector>
#include "../Managers/GameManager.h"
#include "../Miscellaneous/Singleton.h"
#include "../Miscellaneous/Collection.h"
#include "../Components/Collision/Collider.h"
#include "../Components/Collision/SpatialHash.h"
#include "../Game/Zone/Zone.h"

#define CollisionMgr CollisionManager::GetInstance()
class CollisionManager: public Collection<Collider>, public Singleton<CollisionManager> {
	friend class Singleton;
public:
	std::vector<ZoneColliderData> staticColliders;
	SpatialHash spatialHash{ 4000, 4000, 80 };

	void AddStaticColliders(const std::vector<ZoneColliderData>& colliders);
	void ResetSpatialHash();
	void Update();
	void UpdateCollection();

	bool IsPositionMovable(const Rect& rect);

private:
	CollisionManager(): Collection<Collider>(100000) {}
	~CollisionManager() {}
	CollisionManager(CollisionManager const&) = delete;
	void operator=(CollisionManager const&) = delete;
};